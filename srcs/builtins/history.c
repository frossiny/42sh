/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:03:36 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/30 20:27:57 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <shell.h>
#include <utils.h>

/*
** Will clear hist and free linked list
*/

int		empty_hist(t_shell *shell)
{
	t_histo_lst		*history;
	t_histo_lst		*hist_tmp;

	history = shell->history.lst;
	while (history)
	{
		hist_tmp = history;
		history = history->prev;
		ft_strdel(&history->str);
		free(history);
		history = NULL;
	}
	shell->history.lst = NULL;
	return (0);
}

/*
** Will print last 500 hist var
*/

int		b_history(t_cmd *cmd, t_shell *shell)
{
	t_histo_lst		*history;
	int				counter;

	counter = 0;
	(void)cmd;
	history = shell->history.lst;
	while (history->next && counter != 500)
	{
		history = history->next;
		counter++;
	}
	while (history)
	{
		ft_printf("  %zu  %s\n", history->index, history->str);
		history = history->prev;
	}
	return (0);
}
