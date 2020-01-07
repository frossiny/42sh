/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:19:27 by alagroy-          #+#    #+#             */
/*   Updated: 2019/12/02 17:09:32 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARITHMETIC_H
# define ARITHMETIC_H
# include "structs.h"
# include "libft.h"
# define NBR_SYM 12
# define NBR_AE_VAL 15
# define NBR_TYPE 9
# define AEPFAILURE -1
# define AEPSUCCESS -2

t_list				*lex_ae_str(char *str);
long				ft_atol(char *str);
int					parse_aetoken(t_list *token_list);
int					ae_is_bool(t_list *token_list);
long				eval_ae(t_list *token_list);
t_list				*create_test_list(t_list *token_list, int size);
t_list				*copy_ae_token(t_list *elem);
void				del_ae_token(void *content, size_t content_size);
long				eval_expr(t_list *expr);
long				ae_sum(long a, long b);
long				ae_sub(long a, long b);
long				ae_mult(long a, long b);
long				ae_div(long a, long b);
long				ae_mod(long a, long b);
long				eval_test(t_list *test_list);
long				ae_equ(long, long);
long				ae_nequ(long, long);
long				ae_great(long, long);
long				ae_greateq(long, long);
long				ae_less(long, long);
long				ae_lesseq(long, long);
long				ae_and(long, long);
long				ae_or(long, long);
void				remove_or(t_list *mem_left);
char				*ae_base10(char *str);
char				*ft_ltoa(long nb);
long				ft_atol_base(char *str, int base);
int					replace_ae_token(t_token *token);
void				eval_var(char *str);
int					ae_process(t_token *token);

#endif
