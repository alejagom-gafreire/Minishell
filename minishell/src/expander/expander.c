/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:05:20 by gafreire          #+#    #+#             */
/*   Updated: 2025/08/14 18:15:21 by gafreire         ###   ########.fr       */
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
    size_t i = 0, out_len = 0;
    char st_buf[32];

    if (!s) return 0;
    while (s[i]) {
        if (s[i] != '$') { out_len++; i++; continue; }

        if (s[i + 1] == '\0') { out_len++; i += 1; continue; } /* '$' final -> literal */

        if (s[i + 1] == '?') {
            const char *sv = itoa_status(last_status, st_buf);
            out_len += strlen(sv);
            i += 2;
            continue;
        }

        if (is_var_start(s[i + 1])) {
            size_t st = i + 1, en = st + 1;
            while (s[en] && is_var_char(s[en])) en++;
            size_t nlen = en - st;
            char *name = (char *)malloc(nlen + 1);
            if (!name) return out_len; /* sin memoria: devolvemos lo medido */
            for (size_t k = 0; k < nlen; ++k) name[k] = s[st + k];
            name[nlen] = '\0';
            const char *val = getenv(name);
            if (!val) val = "";
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

    while (s && s[i]) {
        if (s[i] != '$') { dst[p++] = s[i++]; continue; }

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
static char *expand_vars_two_pass(const char *s, int last_status) {
    if (!s) return dup_cstr("");
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
static void free_lexer_node(t_lexer *node) {
    if (!node) return;
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
    while (node) {
        if (is_word_token(node->token)) {
            /* 1) Expandir según kind */
            if (node->kind == T_SQ) 
			{
                /* simples: literal */
            } else if (node->kind == T_DQ || node->kind == T_PLAIN) {
                char *expanded = expand_vars_two_pass(node->inf ? node->inf : "", last_status);
                if (!expanded) return 1; /* fallo memoria */
                free(node->inf);
                node->inf = expanded;
            }

            /* 2) Tratar vacíos por tipo */
            int is_empty = (!node->inf || node->inf[0] == '\0');

            if (node->token == T_INFILE || node->token == T_OUTFILE) {
                if (is_empty) {
                    /* ambiguous redirect */
                    write(2, "minishell: ambiguous redirect\n", 30);
                    return 1;
                }
                /* avanzar normal */
                prev = node;
                node = node->next;
                continue;
            }

            if (node->token == T_NAME_CMD || node->token == T_GENERAL) {
                if (is_empty && node->kind == T_PLAIN) {
                    /* borrar nodo de la lista */
                    t_lexer *to_del = node;
                    if (prev == NULL) {
                        *lexer_list = node->next;
                        node = *lexer_list;
                    } else {
                        prev->next = node->next;
                        node = prev->next;
                    }
                    free_lexer_node(to_del);
                    continue; /* importante: ya actualizamos node */
                }
            }
        }
        /* Operador o word conservado -> avanzar normal */
        prev = node;
        node = node->next;
    }
    return 0;
}

// // Helpers para reconocer tokens y nombre de variable
// // static int is_op_token(int t) {
// //     return (t == T_PIPE || t == T_REDIR_IN || t == T_REDIR_OUT);
// // }
// static int is_word_token(int t) {
//     return (t == T_NAME_CMD || t == T_GENERAL || t == T_INFILE || t == T_OUTFILE);
// }
// static int is_var_start(char c) {
//     return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
// }
// static int is_var_char(char c) {
//     return is_var_start(c) || (c >= '0' && c <= '9');
// }

// // Devuelve malloc con el nombre de variable tras el PRIMER '$' en s.
// // Si es "$?" devuelve "?".
// // Si no hay nombre válido, devuelve NULL.
// // Además, si quieres, te da los índices de la zona [start..end) del nombre.
// static char *extract_var_after_dollar(const char *s, size_t *dollar_idx_out,
//                                       size_t *start_out, size_t *end_out) {
//     size_t i, start, end;

//     if (!s) return NULL;

//     // 1) Buscar primer '$'
//     for (i = 0; s[i] && s[i] != '$'; ++i) {}
//     if (s[i] != '$') return NULL; // no hay '$'

//     // 2) Si '$' es el último char, no hay nombre
//     if (s[i+1] == '\0') return NULL;

//     // 3) Caso especial "$?"
//     if (s[i+1] == '?') {
//         if (dollar_idx_out) *dollar_idx_out = i;
//         if (start_out) *start_out = i + 1;
//         if (end_out) *end_out = i + 2; // solo un char '?'
//         char *out = (char *)malloc(2);
//         if (!out) return NULL;
//         out[0] = '?';
//         out[1] = '\0';
//         return out;
//     }

//     // 4) Nombre normal: [A-Za-z_][A-Za-z0-9_]*
//     start = i + 1;
//     if (!is_var_start(s[start])) {
//         // No empieza por letra/_  → no hay nombre válido justo tras '$'
//         return NULL;
//     }
//     end = start + 1;
//     while (s[end] && is_var_char(s[end])) end++;

//     size_t len = end - start;
//     char *out = (char *)malloc(len + 1);
//     if (!out) return NULL;
//     for (size_t k = 0; k < len; ++k) out[k] = s[start + k];
//     out[len] = '\0';

//     if (dollar_idx_out) *dollar_idx_out = i;
//     if (start_out) *start_out = start;
//     if (end_out) *end_out = end;
//     return out;
// }

// // Tu función: ahora solo demuestra cómo obtener "prueba" (el nombre)
// // y enseñarte qué harías con getenv(). Aún no construye el token final.
// int expand_tokens(t_lexer **lexer_list, char **envp) {
//     (void)envp; // de momento no usamos getenv para sustituir todo, solo demo
//     t_lexer *node = (lexer_list ? *lexer_list : NULL);

//     while (node) {
//         if (is_word_token(node->token)) {
//             if (node->kind == T_SQ) {
//                 // Literal, no expandas
//                 // printf("Literal (SQ): %s\n", node->inf ? node->inf : "(null)");
//             } else if (node->kind == T_DQ || node->kind == T_PLAIN) {
//                 size_t di=0, st=0, en=0;
//                 char *prueba = extract_var_after_dollar(node->inf, &di, &st, &en);
//                 if (prueba) {
//                     // Aquí tienes SOLO el nombre tras el '$'
//                     // - Si prueba == "?" → es $?
//                     // - Si es normal → úsalo con getenv(prueba)
//                     // Ejemplo de uso (solo debug):
//                     // char *val = (prueba[0] == '?' && prueba[1] == '\0') ? itoa(last_status) : getenv(prueba);
//                     printf("Nombre var: '%s'\n", prueba);
//                     free(prueba);
//                 } else {
//                     // No hay nombre válido tras '$' (o no hay '$')
//                     // printf("Sin variable válida en: %s\n", node->inf ? node->inf : "(null)");
//                 }
//             }
//         }
//         node = node->next;
//     }
//     return 0;
// }


// int	expand_tokens(t_lexer **lexer_list, char **envp)
// {
// 	t_lexer *temp;

// 	temp = (*lexer_list);

// 	(void)envp;
// 	while (temp)
// 	{
// 		if (temp->token != T_REDIR_IN && temp->token != T_REDIR_OUT
// 			&& temp->token != T_PIPE)
// 		{
// 			if (temp->kind == T_SQ)
// 				printf("Se imprime literal -> %s\n", temp->inf);
// 			else
// 			{
// 				if (temp->kind == T_DQ)
// 				{
// 					int i = ft_strlen(temp->inf);
// 					int z = 0;
// 					// char *prueba = malloc(sizeof(ft_strlen(temp->inf)));
// 					while (z < i && temp->inf[z] != '$')
// 						z++;
// 					int start = z + 1;
// 					int j = start;
// 					printf("TAMAÑO PAPI%d\n", z);
// 					int x = 0;
// 					while (temp->inf[j] != '\0')
// 					{
// 						prueba[x] = temp->inf[z];
// 						x++;
// 						z++;
// 					}
// 					printf("Se expande ->%s\n", prueba);
// 				}
// 				// printf("Se expande -> %s\n",temp->inf);
// 				else if (temp->kind == T_PLAIN)
// 					printf("Se expande -> %s\n", temp->inf);
// 			}
// 			// printf("%s\n",(*temp)->token);
// 			// getenv()
// 		}
// 		temp = temp->next;
// 	}
// 	return (1);
// }