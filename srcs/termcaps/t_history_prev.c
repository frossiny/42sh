/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_history_prev.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:57:50 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/22 17:41:27 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void		termcaps_history_prev(char **str, t_cursor_pos *pos
		, t_shell *shell)
{
	size_t		i;
	t_histo_lst	*curr;

	if (!shell->history.lst || shell->history.pos == 0 || pos->visual_mode)
		return ;
	curr = NULL;
	if (str)
		free(*str);
	if (--(shell->history.pos) == 0)
		*str = shell->history.first_command
			? ft_strdup(shell->history.first_command) : ft_strdup("");
	else
	{
		curr = shell->history.lst;
		i = 0;
		while (++i < shell->history.pos && curr->next)
			curr = curr->next;
		while (!ft_strcmp(curr->str, *str) && curr->prev)
		{
			shell->history.pos--;
			curr = curr->prev;
		}
		*str = ft_strdup(curr->str);
	}
	pos->x_rel = ft_strlen(*str);
}
