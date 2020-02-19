/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_up.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:58:16 by vsaltel           #+#    #+#             */
/*   Updated: 2019/05/02 20:26:25 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		termcaps_up(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)shell;
	(void)str;
	if (!str || !*str)
		return ;
	pos->x_rel -= pos->x_max + 1;
}
