/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_end.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:01:57 by vsaltel           #+#    #+#             */
/*   Updated: 2019/05/15 14:48:28 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void		termcaps_end(char **str, t_cursor_pos *pos, t_shell *shell)
{
	(void)shell;
	if (!str || !*str)
		return ;
	pos->x_rel = ft_strlen(*str);
}
