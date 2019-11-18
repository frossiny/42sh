/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_visual_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:30:28 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/18 14:39:13 by vsaltel          ###   ########.fr       */
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
		term_print(l);
	if (m)
		term_print(m);
	write(1, "\e[0m", 4);
	if (r)
		term_print(r);
	ft_multifree(&l, &m, &r);
}

void		visual_delete(char **str, t_cursor_pos *pos)
{
	if (!pos->visual_mode)
		return ;
	if (pos->v_beg < pos->x_rel)
	{
		*str = ft_strfcut(*str, pos->v_beg, pos->x_rel);
		reprint(*str, pos, pos->v_beg);
	}
	else
	{
		*str = ft_strfcut(*str, pos->x_rel, pos->v_beg);
		reprint(*str, pos, pos->x_rel);
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
