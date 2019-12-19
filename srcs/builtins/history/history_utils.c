/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 14:00:56 by vsaltel           #+#    #+#             */
/*   Updated: 2019/12/19 14:17:20 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include "builtins.h"

/*
** Will print last hist var depending on $HISTSIZE
*/

int		print_hist(t_shell *shell, int size)
{
	t_histo_lst		*history;
	int				counter;

	if (!shell->history.lst || size < 1)
		return (0);
	counter = 1;
	history = shell->history.lst;
	while (history->next && counter != size)
	{
		history = history->next;
		counter++;
	}
	while (history)
	{
		ft_printf("   %2zu  %s\n", history->index, history->str);
		history = history->prev;
	}
	return (0);
}

void	delete_elem_hist(t_history *hist, t_histo_lst *elem)
{
	if (!elem->prev && elem->next)
	{
		elem->next->prev = NULL;
		hist->lst = elem->next;
	}
	else if (!elem->next && elem->prev)
	{
		hist->first_element = elem->prev;
		elem->prev->next = NULL;
	}
	else if (!elem->next && !elem->prev)
	{
		hist->lst = NULL;
		hist->first_element = NULL;
	}
	else
	{
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
	}
	ft_strdel(&elem->str);
	free(elem);
	hist->size--;
}
