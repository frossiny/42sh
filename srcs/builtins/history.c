/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:03:36 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/30 20:09:18 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <shell.h>
#include <utils.h>

int			b_history(t_cmd *cmd, t_shell *shell)
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
		ft_printf("  %zu  %s\n", history->index , history->str);
		history = history->prev;
	}
	return (0);
}
