/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:54:13 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/09 17:24:37 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <fcntl.h>
#include "builtins.h"
#include "history.h"

static void	replace_elem(t_shell *shell, char *ret)
{
	if (shell->history.lst && isatty(0))
	{
		ft_strdel(&shell->history.lst->str);
		shell->history.lst->str = ret;
		shell->history.lst->len = ft_strlen(ret);
	}
	else
		add_to_history(ret, &shell->history);
}

/*
** Will parse cmd to add good variable to hist
*/

void		replace_curr_hist(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		e;
	int		k;
	char	*ret;

	e = 1;
	while (cmd->args[e] && !ft_strcmp(cmd->args[e], "-s"))
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
	replace_elem(shell, ret);
}

/*
** Will clear hist and free linked list -c option
*/

int			empty_hist(t_shell *shell)
{
	t_histo_lst		*history;
	t_histo_lst		*hist_tmp;

	if (!shell->history.lst)
		return (0);
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
	return (0);
}

/*
** Delete one element of history -d option
*/

int			delone_hist(t_history *hist, char *value)
{
	size_t		counter;
	t_histo_lst	*history;
	size_t		index;

	counter = 0;
	index = (ft_strisdigit(value)) ? (size_t)ft_atoi(value) : 0;
	if (index > hist->size || index < 1)
	{
		ft_dprintf(2,
			"42sh: history: %s: history position out of range\n", value);
		return (1);
	}
	if ((history = hist->lst))
	{
		while (history->next && counter != hist->size
								&& history->index != index)
		{
			history->index--;
			history = history->next;
			counter++;
		}
		delete_elem_hist(hist, history);
		hist->index--;
	}
	return (0);
}

/*
** Append to the history file -a option
*/

void		append_hist(t_histo_lst *histo)
{
	t_histo_lst	*curr;
	char		*path;
	int			fd;

	if (!histo)
		return ;
	fd = 0;
	path = ft_strpathfile(getenv("HOME"), ".42sh_history");
	if ((fd = open(path, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR)) != -1)
	{
		curr = histo;
		while (curr)
		{
			ft_dprintf(fd, "%s\n", curr->str);
			curr = curr->next;
		}
		close(fd);
	}
	free(path);
}
