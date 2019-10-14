/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_down.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:57:00 by vsaltel           #+#    #+#             */
/*   Updated: 2019/05/02 20:27:55 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	termcaps_down(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)shell;
	if (!str || !*str)
		return ;
	pos->x_rel += pos->x_max + 1;
}
