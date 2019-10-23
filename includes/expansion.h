/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 17:24:02 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/23 14:37:28 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>

typedef struct	s_expansion
{
	size_t	i;
	size_t	li;
	char	isquote;
	char	*str;
}				t_expansion;

typedef struct	s_globing_list
{
	char			*path;
	char			*content;
	struct s_globing_list	*next;
}				t_globing_list;

typedef struct	s_globing
{
	int			root;
	int			nb_file;
	t_token			*token;
	t_globing_list		*list;
}				t_globing;

int				dir_globing(t_globing *glob, t_globing_list *list, char *path);
#endif
