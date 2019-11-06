/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 17:24:02 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/06 16:00:28 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>
# include "structs.h"

typedef struct	s_expansion
{
	size_t	i;
	size_t	li;
	char	isquote;
	char	*str;
	char	*new;
}				t_expansion;

int				expand(t_token *tokens);
void			exp_set_struct(t_expansion *exp, char *content);
void			exp_join(t_expansion *e, char *tmp);

int				handle_home(t_token *token, t_var *vars);
int				exp_remove_quotes(t_expansion *e);
char			*strjoin_escape(char *s1, char *s2);
char			*strdup_escape(char *str);

int				exp_variables(t_token *token);
t_var			*exp_get_var(t_expansion *exp);
char			*exp_get_varname(t_expansion *exp);
int				exp_simple_var(t_expansion *exp);
int				exp_parameter(t_expansion *exp);

char			*exp_par_len(t_expansion *exp);
int				exp_par_colon(t_expansion *exp, t_var *var, char *name);

#endif
