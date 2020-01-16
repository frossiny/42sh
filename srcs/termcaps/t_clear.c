/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_clear.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:13:12 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/16 14:50:30 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>

#include "libft.h"
#include "shell.h"
#include "termcaps.h"

void		termcaps_clear(char **str, t_cursor_pos *pos, t_shell *shell)
{
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	pos->y_min = 0;
	reprint(*str, pos, g_pos.x_rel, 0);
}
