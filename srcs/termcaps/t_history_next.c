/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_history_next.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:58:32 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/22 17:43:51 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void		termcaps_history_next(char **str, t_cursor_pos *pos
		, t_shell *shell)
{
	size_t		i;
	t_histo_lst	*curr;

	if (!shell->history.lst || shell->history.pos == shell->history.size
			|| pos->visual_mode)
		return ;
	if (shell->history.pos < shell->history.size)
		shell->history.pos++;
	curr = shell->history.lst;
	i = 0;
	while (++i < shell->history.pos && curr->next)
		curr = curr->next;
	while (!ft_strcmp(curr->str, *str) && curr->next && ++shell->history.pos)
		curr = curr->next;
	if (shell->history.pos == 1 && *str)
	{
		if (shell->history.first_command)
			ft_strdel(&(shell->history.first_command));
		shell->history.first_command = ft_strdup(*str);
	}
	if (str)
		free(*str);
	*str = ft_strdup(curr->str);
	pos->x_rel = ft_strlen(*str);
}
