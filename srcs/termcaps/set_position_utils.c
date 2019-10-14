/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_position_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:24:22 by vsaltel           #+#    #+#             */
/*   Updated: 2019/05/22 17:43:58 by frossiny         ###   ########.fr       */
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

static void		check_cursor_pos(t_cursor_pos *pos)
{
	if (pos->x > 0)
		ft_putchar('\n');
	prompt();
	get_pos(pos);
}

int				memset_pos(t_cursor_pos *pos)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	if (!get_pos(pos))
	{
		move_cursor(0, 0);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		pos->y = 0;
		pos->x = prompt_len();
		return (0);
	}
	check_cursor_pos(pos);
	pos->len_str = 0;
	pos->x_min = pos->x;
	pos->x_rel = 0;
	pos->x_max = w.ws_col - 1;
	pos->y_min = pos->y;
	pos->y_max = w.ws_row;
	pos->compl = 0;
	pos->o_input = NULL;
	pos->visual_mode = 0;
	pos->v_beg = 0;
	pos->search_mode = 0;
	pos->s_str = NULL;
	return (1);
}
