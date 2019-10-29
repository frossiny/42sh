/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 17:24:02 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/29 18:42:48 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>
# include "structs.h"

typedef struct		s_expansion
{
	size_t					i;
	size_t					li;
	char					isquote;
	char					*str;
}					t_expansion;

typedef struct		s_globing_list
{
	char					*path;
	char					*content;
	struct s_globing_list	*next;
}					t_globing_list;

typedef struct		s_globing
{
	int						root;
	int						nb_file;
	t_token					*token;
	t_globing_list			*list;
}					t_globing;

typedef struct		s_compare
{
	char					*cmp;
	char					*file;
}					t_compare;

int					dir_globing(t_globing *glob,
						t_globing_list *list, char *path);
int					complete_str(char *cmp, char *file);
int					next_char(t_compare s, int x, int y);

int					wildcard_question(t_compare s, int x, int y);
int					wildcard_star(t_compare s, int x, int y);
int					wildcard_bracket(t_compare s, int x, int y);

void				free_globing(t_globing_list *list);
t_globing_list		*create_globing(char *str);

void				add_token(t_globing *glob, char *content);
void				free_token(t_token *token);
void				remove_first_token(t_token **token);
void				remove_token(t_token *curr);

int					is_glob_char(char c);
int					is_glob_str(char *str);
char				*pull_multi_occ(char *str, char occ);
#endif
