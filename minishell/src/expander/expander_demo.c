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

/*
 ===================== Reconocimiento =====================     
    Chequeo que token es
*/
int is_operator_token(int t) {
    return (t == T_PIPE || t == T_REDIR_IN || t == T_REDIR_OUT);
}
int is_word_token(int t) {
    return (t == T_NAME_CMD || t == T_GENERAL || t == T_INFILE || t == T_OUTFILE);
}
int is_var_start(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
}
int is_var_char(char c) {
    return is_var_start(c) || (c >= '0' && c <= '9');
}

/*
===================== Expansión optimizada (dos pasadas) ===================== 
 Reglas:
   - $?: sustituir por last_status
   - $NAME: NAME = [A-Za-z_][A-Za-z0-9_]* -> getenv(NAME) o "" si no existe
   - $ seguido de char no válido / fin: se trata como '$' literal
   - No field splitting. No ${}, $1, $$, etc. (quedan literales salvo $? y $NAME)
*/

/* 1ª pasada: medir longitud final */
size_t measure_expanded_len(const char *str, int last_status) {
    size_t i;
    size_t out_len;
    char st_buf[32];
    size_t nlen;
    char *name;
    size_t k;

    i = 0;
    out_len = 0;
    k = 0;

    if (!str) 
        return (0);
    while (str[i] != '\0') 
    {
        if (str[i] != '$') 
        { 
            out_len++; 
            i++; 
            continue; 
        }
        if (str[i + 1] == '\0') 
        { 
            out_len++; 
            i += 1; 
            continue; 
        } /* '$' final -> literal */
        if (str[i + 1] == '?') 
        {
            const char *sv = itoa_status(last_status, st_buf);
            out_len += strlen(sv);
            i += 2;
            continue;
        }
        if (is_var_start(str[i + 1])) 
        {
            size_t st = i + 1;
            size_t en = st + 1;
            while (str[en] && is_var_char(str[en]))
                en++;
            nlen = en - st;
            name = (char *)malloc(nlen + 1);
            if (!name)  /* sin memoria: devolvemos lo medido */
                return (out_len);
            while (k < nlen)
            {
                name[k] = str[st + k];
                k++;
            } 
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
void write_expanded(char *dst, const char *s, int last_status) 
{
    size_t i; 
    size_t p;
    char st_buf[32];
    char *sv;
    size_t L;
    size_t st;
    size_t en;
    size_t nlen;
    char *name;
    size_t k;
    char *val;
    
    i = 0;
    p = 0;
    k = 0;

    while (s && s[i]) 
    {
        if (s[i] != '$') 
        { 
            dst[p++] = s[i++]; 
            continue; 
        }

        if (s[i + 1] == '\0') 
        { 
            dst[p++] = '$'; 
            i += 1; continue; 
        } /* '$' final */

        if (s[i + 1] == '?') 
        {
            sv = itoa_status(last_status, st_buf);
            L = ft_strlen(sv);
            ft_memcpy(dst + p, sv, L);
            p += L; 
            i += 2; 
            continue;
        }
        if (is_var_start(s[i + 1])) 
        {
            st = i + 1;
            en = st + 1;
            while (s[en] && is_var_char(s[en])) 
                en++;
            nlen = en - st;
            name = (char *)malloc(nlen + 1);
            if (!name) {
                /* sin memoria: copia literal lo que queda */
                while (s[i]) dst[p++] = s[i++];
                break;
            }
            while (k < nlen) 
            {
                name[k] = s[st + k];
                k++;
            }
            name[nlen] = '\0';
            val = getenv(name);
            if (!val) 
                val = "";
            L = ft_strlen(val);
            ft_memcpy(dst + p, val, L);
            p += L; 
            i = en;
            free(name);
            continue;
        }
        dst[p++] = '$';
        i += 1;
    }
    dst[p] = '\0';
}

/* Expande TODO en s (para PLAIN/DQ). Devuelve malloc con el resultado. */
char *expand_vars_two_pass(const char *str, int last_status) 
{
    size_t size;
    char *out;

    if (!str)
        return (ft_strdup(""));
    size = measure_expanded_len(str, last_status);
    out = (char *)malloc(size + 1);
    if (!out) 
        return (NULL);
    write_expanded(out, str, last_status);
    return (out);
}
