/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_left_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:58:46 by vsaltel           #+#    #+#             */
/*   Updated: 2019/05/15 14:47:33 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "tokens_list.h"

static int		is_delimiter(char *str)
{
	size_t	i;

	i = 0;
	while (g_tokens_list + i && (g_tokens_list[i]).op)
	{
		if (ft_strncmp(g_tokens_list[i].op, str, 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

void			termcaps_left_word(char **str, t_cursor_pos *pos
		, t_shell *shell)
{
	(void)shell;
	if (!str || !*str)
		return ;
	if (pos->x_rel > 0 && !is_delimiter(*str + pos->x_rel))
		pos->x_rel--;
	while (pos->x_rel > 0 && is_delimiter(*str + pos->x_rel))
		pos->x_rel--;
	while (pos->x_rel > 0 && !is_delimiter(*str + pos->x_rel - 1))
		pos->x_rel--;
}
