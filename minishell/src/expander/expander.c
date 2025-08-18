/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:05:20 by gafreire          #+#    #+#             */
/*   Updated: 2025/08/16 18:00:06 by gafreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




/* ===================== Reconocimiento ===================== */
// static int is_operator_token(int t) {
//     return (t == T_PIPE || t == T_REDIR_IN || t == T_REDIR_OUT);
// }
static int is_word_token(int t) {
    return (t == T_NAME_CMD || t == T_GENERAL || t == T_INFILE || t == T_OUTFILE);
}
static int is_var_start(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
}
static int is_var_char(char c) {
    return is_var_start(c) || (c >= '0' && c <= '9');
}

/* ===================== Expansión optimizada (dos pasadas) ===================== */
/* Reglas:
   - $?: sustituir por last_status
   - $NAME: NAME = [A-Za-z_][A-Za-z0-9_]* -> getenv(NAME) o "" si no existe
   - $ seguido de char no válido / fin: se trata como '$' literal
   - No field splitting. No ${}, $1, $$, etc. (quedan literales salvo $? y $NAME)
*/

/* 1ª pasada: medir longitud final */
static size_t measure_expanded_len(const char *s, int last_status) {
    size_t i = 0;
    size_t out_len = 0;
    char st_buf[32];

    if (!s) 
        return (0);
    while (s[i]) 
    {
        if (s[i] != '$') 
        { 
            out_len++; 
            i++; 
            continue; 
        }
        if (s[i + 1] == '\0') 
        { 
            out_len++; 
            i += 1; 
            continue; 
        } /* '$' final -> literal */
        if (s[i + 1] == '?') 
        {
            const char *sv = itoa_status(last_status, st_buf);
            out_len += strlen(sv);
            i += 2;
            continue;
        }
        if (is_var_start(s[i + 1])) 
        {
            size_t st = i + 1;
            size_t en = st + 1;
            while (s[en] && is_var_char(s[en]))
                en++;
            size_t nlen = en - st;
            char *name = (char *)malloc(nlen + 1);
            if (!name)  /* sin memoria: devolvemos lo medido */
                return (out_len);
            for (size_t k = 0; k < nlen; ++k) 
                name[k] = s[st + k];
            name[nlen] = '\0';
            const char *val = getenv(name);
            if (!val) 
                val = "";
            out_len += strlen(val);
            free(name);
            i = en;
            continue;
        }
        /* nombre inválido -> '$' literal */
        out_len++;
        i += 1;
    }
    return out_len;
}

/* 2ª pasada: escribir el expandido en dst */
static void write_expanded(char *dst, const char *s, int last_status) {
    size_t i = 0, p = 0;
    char st_buf[32];

    while (s && s[i]) 
    {
        if (s[i] != '$') 
        { 
            dst[p++] = s[i++]; 
            continue; 
        }

        if (s[i + 1] == '\0') { dst[p++] = '$'; i += 1; continue; } /* '$' final */

        if (s[i + 1] == '?') {
            const char *sv = itoa_status(last_status, st_buf);
            size_t L = strlen(sv);
            memcpy(dst + p, sv, L);
            p += L; i += 2; continue;
        }

        if (is_var_start(s[i + 1])) {
            size_t st = i + 1, en = st + 1;
            while (s[en] && is_var_char(s[en])) en++;
            size_t nlen = en - st;
            char *name = (char *)malloc(nlen + 1);
            if (!name) {
                /* sin memoria: copia literal lo que queda */
                while (s[i]) dst[p++] = s[i++];
                break;
            }
            for (size_t k = 0; k < nlen; ++k) name[k] = s[st + k];
            name[nlen] = '\0';
            const char *val = getenv(name);
            if (!val) val = "";
            size_t L = strlen(val);
            memcpy(dst + p, val, L);
            p += L; i = en;
            free(name);
            continue;
        }

        dst[p++] = '$';
        i += 1;
    }
    dst[p] = '\0';
}

/* Expande TODO en s (para PLAIN/DQ). Devuelve malloc con el resultado. */
static char *expand_vars_two_pass(const char *s, int last_status) 
{
    if (!s) 
        return (ft_strdup(""));
    size_t L = measure_expanded_len(s, last_status);
    char *out = (char *)malloc(L + 1);
    if (!out) return NULL;
    write_expanded(out, s, last_status);
    return out;
}

/* ===================== Expansión por tokens ===================== */
/* Reglas post-expansión:
   - T_INFILE/T_OUTFILE: si "" => error (ambiguous redirect)
   - T_NAME_CMD/T_GENERAL:
       * "" + kind == T_PLAIN => borrar token
       * "" + kind == T_DQ/T_SQ => conservar argumento vacío
   - Operadores: no se tocan
*/

/* Si liberas en otro sitio centralizado, quita estos free. */
static void free_lexer_node(t_lexer *node) 
{
    if (!node) 
    return;
    free(node->inf);
    free(node);
}

int expand_tokens(t_lexer **lexer_list, int last_status) 
{
    t_lexer *node;
	t_lexer *prev;
    if (!lexer_list) 
		return (0);
    node = *lexer_list;
    prev = NULL;
    while (node) 
    {
        if (is_word_token(node->token)) 
        {
            if (node->kind == T_DQ || node->kind == T_PLAIN) 
            {
                char *expanded = expand_vars_two_pass(node->inf, last_status);
                if (!expanded) 
                    return (1);
                free(node->inf);
                node->inf = expanded;
            }
            int is_empty = (!node->inf || node->inf[0] == '\0');
            if (node->token == T_INFILE || node->token == T_OUTFILE) {
                if (is_empty)
                {
                    printf("minishell: ambiguous redirect\n");
                    return (1);
                }
                prev = node;
                node = node->next;
                continue;
            }

            if (node->token == T_NAME_CMD || node->token == T_GENERAL) 
            {
                if (is_empty && node->kind == T_PLAIN) {
                    t_lexer *to_del = node;
                    if (prev == NULL) {
                        *lexer_list = node->next;
                        node = *lexer_list;
                    } else {
                        prev->next = node->next;
                        node = prev->next;
                    }
                    free_lexer_node(to_del);
                    continue;
                }
            }
        }
        prev = node;
        node = node->next;
    }
    return (0);
}
