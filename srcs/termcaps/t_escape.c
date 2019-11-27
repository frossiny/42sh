/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_escape.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:09:40 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/27 15:11:51 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		termcaps_escape(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)shell;
	(void)str;
	if (pos->search_mode)
	{
		ft_strdel(&pos->s_str);
		pos->search_mode = 0;
	}
}
