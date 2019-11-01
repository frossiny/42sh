/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:03:36 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/01 19:25:13 by lubenard         ###   ########.fr       */
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
	shell->history.index = 1;
	shell->history.lst = NULL;
	return (0);
}

int		print_history(t_shell *shell)
{
	t_histo_lst		*history;
	size_t			counter;

	counter = 0;
	history = shell->history.lst;
	while (history->next && counter != shell->history.index)
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

/*
** Will print last hist var depending on $HISTSIZE
*/

#include <stdio.h>

int		b_history(t_cmd *cmd, t_shell *shell)
{
	t_options	opts;

	(void)cmd;
	opts = opt_parse(cmd, "cdanrwps", "history");
	while (opts->opts && opts->opts->next)
	{
		printf("option = %s\n");
		opts->opts = opts->opts->next;
	}
	//print_history(shell);
	//empty_hist(shell);
	return (0);
}
