/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_visual_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:30:28 by vsaltel           #+#    #+#             */
/*   Updated: 2020/02/13 16:31:08 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void		visual_print(char *str, t_cursor_pos *pos)
{
	char *l;
	char *m;
	char *r;

	if (pos->v_beg < pos->x_rel)
	{
		l = ft_strndup(str, pos->v_beg);
		m = ft_strndup(str + pos->v_beg, pos->x_rel - pos->v_beg + 1);
		r = str[pos->x_rel] ? ft_strdup(str + pos->x_rel + 1) : NULL;
	}
	else
	{
		l = ft_strndup(str, pos->x_rel);
		m = ft_strndup(str + pos->x_rel, pos->v_beg - pos->x_rel + 1);
		r = str[pos->v_beg] ? ft_strdup(str + pos->v_beg + 1) : NULL;
	}
	if (l)
		term_print(g_fd, l);
	write(1, "\e[7m", 4);
	if (m)
		term_print(g_fd, m);
	write(1, "\e[0m", 4);
	if (r)
		term_print(g_fd, r);
	ft_multifree(&l, &m, &r);
}

void		visual_delete(char **str, t_cursor_pos *pos)
{
	if (!pos->visual_mode)
		return ;
	if (pos->v_beg < pos->x_rel)
	{
		*str = ft_strfcut(*str, pos->v_beg, pos->x_rel);
		reprint(*str, pos, pos->v_beg, 0);
	}
	else
	{
		*str = ft_strfcut(*str, pos->x_rel, pos->v_beg);
		reprint(*str, pos, pos->x_rel, 0);
	}
	pos->visual_mode = 0;
	pos->v_beg = 0;
	ft_strdel(&pos->v_str);
}

void		termcaps_visual_mode(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)str;
	(void)shell;
	if (!str || !*str)
		return ;
	if (!pos->visual_mode)
	{
		pos->visual_mode = 1;
		pos->v_beg = pos->x_rel;
	}
	else
	{
		pos->visual_mode = 0;
		pos->v_beg = 0;
		ft_strdel(&pos->v_str);
	}
}
