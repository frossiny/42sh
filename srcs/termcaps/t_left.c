/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_left.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:33:37 by vsaltel           #+#    #+#             */
/*   Updated: 2019/05/02 20:27:27 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		termcaps_left(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)shell;
	(void)str;
	if (!str || !*str)
		return ;
	if (pos->x_rel > 0)
		pos->x_rel--;
}
