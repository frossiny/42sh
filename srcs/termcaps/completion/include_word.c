/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 17:49:04 by frossiny          #+#    #+#             */
/*   Updated: 2019/08/12 17:55:17 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void		include_word(char *word, char **str, t_cursor_pos *pos)
{
	char	*left;
	char	*right;
	size_t	i;
	size_t	j;

	i = pos->x_rel;
	if (pos->o_input)
		free(pos->o_input);
	pos->o_input = ft_strdup(*str);
	pos->opos = pos->x_rel;
	while (i > 0 && !ft_isspace((*str)[i - 1]))
		i--;
	left = ft_strndup(*str, i);
	pos->x_rel = i + ft_strlen(word);
	j = i;
	while ((*str)[j] && !ft_isspace((*str)[j]))
		j++;
	right = ft_strdup(*str + j);
	left = ft_strfjoin(left, word, left);
	ft_strdel(str);
	*str = ft_strfjoin(left, right, right);
	ft_strdel(&left);
}
