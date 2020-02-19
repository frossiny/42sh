/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_delete_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:04:57 by vsaltel           #+#    #+#             */
/*   Updated: 2019/05/15 14:48:08 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void	del_char_right(char **str, t_cursor_pos *pos)
{
	char *l;
	char *r;

	if (pos->x_rel)
	{
		l = ft_strndup(*str, pos->x_rel);
		r = ft_strdup(*str + pos->x_rel + 1);
	}
	else
	{
		l = ft_strdup("");
		r = ft_strdup(*str + 1);
	}
	*str = ft_strfjoin(l, r, *str);
	free(l);
	free(r);
}

void		termcaps_delete_right(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)shell;
	if (!str || !*str)
		return ;
	if (pos->visual_mode)
		visual_delete(str, pos);
	else if ((*str)[pos->x_rel])
		del_char_right(str, pos);
}
