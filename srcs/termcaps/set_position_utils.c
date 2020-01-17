/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_position_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:24:22 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/16 14:59:39 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <sys/ioctl.h>
#include "libft.h"
#include "shell.h"

void			move_cursor(int x, int y)
{
	char	*tmp;
	char	*tmp2;

	tmp = tgetstr("cm", NULL);
	tmp2 = tgoto(tmp, x, y);
	tputs(tmp2, 1, ft_putchar);
}

int				get_pos(t_cursor_pos *pos)
{
	int		i;
	char	buf[17];

	write(1, "\033[6n", 4);
	if ((i = read(0, buf, 16)) <= 0)
		return (0);
	buf[i] = 0;
	i = 0;
	while (buf[i])
	{
		if (buf[i] == '[')
			pos->y = ft_atoi(&buf[i + 1]) - 1;
		if (buf[i] == ';')
			pos->x = ft_atoi(&buf[i + 1]) - 1;
		i++;
	}
	return (1);
}

static void		memset_cursor(t_cursor_pos *pos)
{
	int				ret;

	ret = get_pos(pos);
	if (!ret)
	{
		move_cursor(0, 0);
		prompt();
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		pos->y = 0;
		pos->x = prompt_len();
		move_cursor(pos->x, pos->y);
	}
	else
	{
		if (pos->x > 0)
		{
			ft_putchar('\n');
			if (pos->y + 1 != pos->y_max)
				pos->y++;
		}
		prompt();
		pos->x = prompt_len();
		move_cursor(pos->x, pos->y);
	}
}

void			memset_pos(t_cursor_pos *pos)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	pos->x_max = w.ws_col - 1;
	pos->y_max = w.ws_row;
	memset_cursor(pos);
	pos->x_min = pos->x;
	pos->y_min = pos->y;
	pos->lx = pos->x;
	pos->ly = pos->y;
}
