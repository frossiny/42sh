/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 13:17:57 by vsaltel           #+#    #+#             */
/*   Updated: 2019/05/15 14:20:48 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "shell.h"

void		resize(int sig)
{
	struct winsize	w;
	t_cursor_pos	tmp;

	(void)sig;
	ioctl(0, TIOCGWINSZ, &w);
	if (!get_pos(&tmp))
	{
		if (tmp.y != g_pos.y)
		{
			if (tmp.x < g_pos.x)
				g_pos.y_min--;
			if (tmp.x > g_pos.x)
				g_pos.y_min++;
		}
	}
	g_pos.x_max = w.ws_col - 1;
	g_pos.y_max = w.ws_row;
	reprint(g_pos.str, &g_pos, g_pos.x_rel);
}
