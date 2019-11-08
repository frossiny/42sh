/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:16:03 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/08 17:43:02 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"

/*
** Will parse cmd to add good variable to hist
*/

void	parse_and_add_hist(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		e;
	int		k;
	char	*ret;

	e = 1;
	while (cmd->args[e] && cmd->args[e][0] == '-')
		e++;
	k = e;
	i = 0;
	if (!cmd->args[e])
		return ;
	while (cmd->args[e + 1])
		i += ft_strlen(cmd->args[e++]) + 1;
	i += ft_strlen(cmd->args[e]);
	if (!(ret = ft_strnew(i)))
		return ;
	while (cmd->args[k + 1])
	{
		ft_strcat(ret, cmd->args[k++]);
		ft_strcat(ret, " ");
	}
	ft_strcat(ret, cmd->args[k]);
	ft_strdel(&shell->history.lst->str);
	shell->history.lst->str = ret;
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
