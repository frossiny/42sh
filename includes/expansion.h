/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 17:24:02 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/06 18:32:42 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>
# include "structs.h"

typedef struct		s_expansion
{
	size_t	i;
	size_t	li;
	char	isquote;
	char	*str;
	char	*new;
}					t_expansion;

typedef struct		s_globbing_list
{
	char					*path;
	char					*content;
	struct s_globbing_list	*next;
}					t_globbing_list;

typedef struct		s_globbing
{
	int						root;
	int						nb_file;
	t_token					*token;
	t_globbing_list			*list;
}					t_globbing;

typedef struct		s_compare
{
	char					*cmp;
	char					*file;
}					t_compare;

int					expand(t_token *tokens);
void				exp_set_struct(t_expansion *exp, char *content);
void				exp_join(t_expansion *e, char *tmp);

int					handle_home(t_token *token, t_var *vars);
int					exp_remove_quotes(t_expansion *e);
char				*strjoin_escape(char *s1, char *s2);
char				*strdup_escape(char *str);

int					exp_variables(t_token *token);
t_var				*exp_get_var(t_expansion *exp);
char				*exp_get_varname(t_expansion *exp);
int					exp_simple_var(t_expansion *exp);
int					exp_parameter(t_expansion *exp);

char				*exp_par_len(t_expansion *exp);
int					exp_par_colon(t_expansion *exp, t_var *var, char *name);

int					dir_globbing(t_globbing *glob,
						t_globbing_list *list, char *path);
int					complete_str(char *cmp, char *file);
int					next_char(t_compare s, int x, int y);

int					wildcard_question(t_compare s, int x, int y);
int					wildcard_star(t_compare s, int x, int y);
int					wildcard_bracket(t_compare s, int x, int y);

void				free_globbing(t_globbing_list *list);
t_globbing_list		*create_globbing(char *str);

void				add_token(t_globbing *glob, char *content);
void				free_token(t_token *token);
void				remove_first_token(t_token **token);
void				remove_token(t_token *curr);

int					is_glob_char(char c);
int					is_glob_str(char *str);
char				*pull_multi_occ(char *str, char occ);

#endif
