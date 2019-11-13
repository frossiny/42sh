/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:16:03 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/13 18:48:45 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"

void	delone_hist(t_history *hist, int index)
{
	size_t		counter;
	t_histo_lst	*history;
	t_histo_lst	*start;

	counter = 0;
	history = hist->lst;
	start = hist->lst;
	while (history->next && counter != hist->size && (int)history->index != index)
	{
		history = history->next;
		counter++;
	}
	while (start->next && (int)start->index != index)
	{
		start->index--;
		start = start->next;
	}
	if (index == 1)
		hist->lst = hist->lst->next;
	else
	{
		history->prev->next = history->next;
		history->next->prev = history->prev;
	}
	ft_strdel(&history->str);
	free(history);
	hist->index--;
}

/*
** Will parse cmd to add good variable to hist
*/

void	replace_curr_hist(t_shell *shell, char *to_add)
{
	if (!to_add)
		return ;
	ft_strdel(&shell->history.lst->str);
	shell->history.lst->str = ft_strdup(to_add);
}

/*
** Will clear hist and free linked list
*/

void	empty_hist(t_shell *shell)
{
	t_histo_lst		*history;
	t_histo_lst		*hist_tmp;

	history = shell->history.lst;
	while (history)
	{
		hist_tmp = history;
		history = history->prev;
		ft_strdel(&hist_tmp->str);
		free(hist_tmp);
	}
	shell->history.index = 1;
	shell->history.lst = NULL;
}
