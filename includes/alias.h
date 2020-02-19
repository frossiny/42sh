/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:03:49 by vsaltel           #+#    #+#             */
/*   Updated: 2020/02/18 14:47:43 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_H
# define ALIAS_H

# include "structs.h"

typedef struct		s_string
{
	char			*str;
	struct s_string	*next;
}					t_string;

void				alias_patch_token_list(t_token *dest, t_token *new);
int					alias_new(t_alias **alias, char *key, char *value);
t_alias				*alias_get(t_alias *alias, char *key);
int					alias_recursive(t_alias *alias, t_token *token,
											t_string *hist, char *old_word);
int					alias_lex(t_lexer *lexer, char **input);
void				alias_display_all(t_alias *alias);
void				alias_free_all(t_alias **list);
int					alias_display_one(t_alias *alias, char *key);
void				alias_free_one(t_alias *alias);
int					alias_resolve(t_alias *alias, t_token *token,
														t_string *hist);
int					alias_exec(t_shell *shell);

void				free_alias_history(t_string **list);

int					is_already_solve(t_string *list, char *str);
t_string			*add_alias_history(t_string *list, char *str);
void				free_alias_history(t_string **list);
t_string			*t_stringdup(t_string *input);
#endif
