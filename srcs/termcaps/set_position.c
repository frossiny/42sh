/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:59:44 by vsaltel           #+#    #+#             */
/*   Updated: 2020/02/13 17:05:06 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "libft.h"
#include "shell.h"

static void		move_pos(char *str, t_cursor_pos *pos, int len_dest)
{
	pos->len_str = ft_strlen(str);
	if (len_dest < 0)
		len_dest = 0;
	else if (len_dest > pos->len_str)
		len_dest = pos->len_str;
	pos->x_rel = len_dest;
	pos->x = pos->x_min;
	pos->y = pos->y_min;
	if (pos->x == pos->x_max || pos->x + len_dest > pos->x_max)
	{
		pos->y += (pos->x + 1 + len_dest) / (pos->x_max + 1);
		pos->x = ((pos->x + 1 + len_dest) % (pos->x_max + 1)) - 1;
		if (pos->x == -1)
		{
			pos->y--;
			pos->x = pos->x_max;
		}
	}
	else
		pos->x += len_dest;
	pos->y = pos->y < 0 ? 0 : pos->y;
	move_cursor(pos->x, pos->y);
	pos->y_min = pos->y_min < 0 ? 0 : pos->y_min;
}

static void		last_line(char *str, t_cursor_pos *pos)
{
	long	len;
	long	i;

	if (pos->search_mode)
		len = (pos->x_min + ft_strlen(str) +
			ft_strlen("history_search: _") + ft_strlen(pos->s_str) +
				pos->x_max + 1) / (pos->x_max + 1);
	else
		len = (pos->x_min + ft_strlen(str) + 1) / (pos->x_max + 1);
	if (len + pos->y_min >= pos->y_max)
	{
		len = pos->y_min + len + 1 - pos->y_max;
		move_cursor(pos->x, pos->y);
		i = -1;
		while (++i < len)
			mytputs(tgetstr("sf", NULL));
		pos->y_min -= len;
		move_cursor(0, pos->y_min < 0 ? 0 : pos->y_min);
	}
}

void			term_print(int fd, char *str)
{
	char	*tmp;
	int		i;

	if (!str)
		return ;
	tmp = ft_strdup(str);
	i = -1;
	while (tmp[++i])
	{
		if (tmp[i] == '\n')
			tmp[i] = ' ';
	}
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
}

void			reprint(char *str, t_cursor_pos *pos, int cursor_pos,
														int is_resize)
{
	t_cursor_pos	tmp;

	if (g_shell.jobs.lst && !is_resize && get_pos(&tmp)
			&& (tmp.x != pos->lx || tmp.y != pos->ly))
	{
		if (tmp.x)
			ft_putchar('\n');
		memset_pos(pos);
	}
	move_cursor(0, (pos->y_min >= 0 ? pos->y_min : 0));
	if (pos->y_min > 0)
		mytputs(tgetstr("cd", NULL));
	else
		mytputs(tgetstr("ce", NULL));
	last_line(str, pos);
	prompt();
	if (pos->visual_mode)
		visual_print(str, pos);
	else
		term_print(g_fd, str);
	if (pos->search_mode)
		ft_printf("\nhistory_search: %s_", pos->s_str);
	move_pos(str, pos, cursor_pos);
	pos->lx = pos->x;
	pos->ly = pos->y;
}

void			final_position(t_cursor_pos *pos)
{
	long	len;

	len = (pos->x_min + pos->len_str + 1) / (pos->x_max + 1);
	if (len + pos->y_min >= pos->y_max - 1)
	{
		move_cursor(0, pos->y_max - 1);
		mytputs(tgetstr("do", NULL));
		move_cursor(0, pos->y_max - 1);
	}
	else
		move_cursor(0, len + pos->y_min + 1);
	mytputs(tgetstr("cd", NULL));
}
