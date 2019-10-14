/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_history_prev.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:57:50 by vsaltel           #+#    #+#             */
/*   Updated: 2019/05/15 14:47:07 by frossiny         ###   ########.fr       */
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
	shell->history.pos--;
	if (shell->history.pos == 0)
		*str = shell->history.first_command
			? ft_strdup(shell->history.first_command) : ft_strdup("");
	else
	{
		curr = shell->history.lst;
		i = 0;
		while (++i < shell->history.pos && curr->next)
			curr = curr->next;
		*str = ft_strdup(curr->str);
	}
	pos->x_rel = ft_strlen(*str);
}
