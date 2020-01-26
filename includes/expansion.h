/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 17:24:02 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/26 17:53:06 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>
# include "structs.h"

# define WHITE "\e[0m"
# define RED "\e[31m"
# define BLACK "\e[30m"
# define GREEN "\e[32m"
# define BROWN "\e[33m"
# define BLUE "\e[34m"
# define PURPLE "\e[35m"
# define CYAN "\e[36m"
# define LGRAY "\e[37m"

typedef struct		s_expansion
{
	size_t	i;
	size_t	li;
	int		rec;
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
	int						l_pattern;
	int						len_find;
}					t_compare;

int					expand(t_token *tokens, int do_globbing, t_cmd *cmd);
void				exp_set_struct(t_expansion *exp, char *content);
void				exp_join(t_expansion *e, char *tmp, int noescape);
t_token				*exp_del_empty_tokens(t_token *token, t_cmd *cmd);

int					handle_home(t_token *token, t_var *vars);
int					exp_remove_quotes(t_token *token);
char				*strjoin_escape(char *s1, char *s2);
char				*strdup_escape(char *str);
char				*dquotes_join_escape(char *s1, char *s2);
char				*dquotes_dup_escape(char *str);

int					exp_variables(t_token *token);
t_var				*exp_get_var(t_expansion *exp);
char				*exp_get_varname(t_expansion *exp);
int					exp_simple_var(t_expansion *exp);
int					exp_parameter(t_expansion *exp);
int					exp_parameter_parse(t_expansion *exp);
char				*exp_get_word(t_expansion *exp);
int					exp_del_pattern(t_expansion *exp, t_var *var);
void				exp_tok_clean(t_token *token);
char				*exp_dup_escape(char *src, t_expansion *exp);

char				*exp_par_len(t_expansion *exp);
int					exp_par_colon(t_expansion *exp, t_var *var, char *name);
int					exp_plus(t_expansion *exp, t_var *var, \
												char *word, char *name);
int					exp_qm(t_expansion *exp, t_var *var, \
												char *word, char *name);
int					exp_equ(t_expansion *exp, t_var *var, \
												char *word, char *name);
int					exp_minus(t_expansion *exp, t_var *var, \
												char *word, char *name);

int					replace_globbing(t_token *token);
int					dir_globbing(t_globbing *glob,
						t_globbing_list *list, char *path);
int					complete_str(char *cmp, char *file);
int					next_char(t_compare *s, int x, int y);

int					wildcard_question(t_compare *s, int x, int y);
int					wildcard_star(t_compare *s, int x, int y);
int					wildcard_bracket(t_compare *s, int x, int y);

void				free_globbing(t_globbing_list *list);
t_globbing_list		*create_globbing(char *str);

void				add_token(t_globbing *glob, char *content);
void				free_token(t_token *token);
void				remove_first_token(t_token *token);

int					is_glob_char(char c);
int					is_glob_str(char *str);
int					is_close_bracket(char *str, int i);
char				*pull_multi_occ(char *str, char occ);

/*
** prompt expansions
*/

void				add_other_char_prompt(char **expanded_prompt,
											char *prompt, int *i);
void				reduce_pwd_size(char **expanded_prompt, char *pwd, int *i);
void				handle_options_h_prompt(char **expanded_prompt,
											int *i, int mode);
void				exec_option_prompt(char **expanded_prompt,
										char *to_add, int *i);
void				handle_options_num_prompt(char **expanded_prompt,
												int num, int *i);

#endif
