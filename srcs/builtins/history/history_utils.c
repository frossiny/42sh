/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:16:03 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/14 18:31:38 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"

/*
** Will clear hist and free linked list
*/

void	empty_hist(t_shell *shell)
{
	t_histo_lst		*history;
	t_histo_lst		*hist_tmp;

	if (shell->history.first_element->index - 1 <= 0)
		shell->history.index = 1;
	else
		shell->history.index = shell->history.first_element->index - 1;
	history = shell->history.lst;
	while (history)
	{
		hist_tmp = history;
		history = history->next;
		ft_strdel(&hist_tmp->str);
		free(hist_tmp);
	}
	shell->history.size = 0;
	shell->history.first_element = NULL;
	shell->history.lst = NULL;
}
