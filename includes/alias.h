/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:03:49 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/17 16:59:12 by frossiny         ###   ########.fr       */
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

void				alias_display_all(t_alias *alias);
int					alias_display_one(t_alias *alias, char *key);
int					alias_new(t_alias **alias, char *key, char *value);
t_alias				*alias_get(t_alias *alias, char *key);
void				alias_free_all(t_alias **list);
void				alias_free_one(t_alias *alias);
int					alias_resolve(t_token *token, t_alias *alias,
													t_string **hist);
int					alias_exec(t_shell *shell, char **input);

void				free_alias_history(t_string **list);

void				set_loop(t_alias *alias);
int					is_already_solve(t_string *list, char *str);
void				maj_alias_history(t_string *list, t_string **hist);
void				add_alias_history(t_string **list, char *str);
void				free_alias_history(t_string **list);
#endif
