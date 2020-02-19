/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_delete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:32:13 by vsaltel           #+#    #+#             */
/*   Updated: 2019/05/15 14:48:01 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void	del_char(char **str, t_cursor_pos *pos)
{
	char *l;
	char *r;

	if (pos->x_rel)
		l = ft_strndup(*str, pos->x_rel - 1);
	else
		l = ft_strdup("");
	r = ft_strdup(*str + pos->x_rel);
	*str = ft_strfjoin(l, r, *str);
	free(l);
	free(r);
}

void		termcaps_delete(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)shell;
	if (pos->search_mode)
		return (history_search_delete(str, pos, &(shell->history)));
	if (!str || !*str)
		return ;
	if (pos->visual_mode)
		visual_delete(str, pos);
	else if (pos->x_rel)
	{
		del_char(str, pos);
		pos->x_rel--;
	}
}
