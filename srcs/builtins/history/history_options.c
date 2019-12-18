/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:54:13 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/18 18:30:33 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <fcntl.h>
#include "builtins.h"
#include "history.h"

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
** Will clear hist and free linked list
*/

void		empty_hist(t_shell *shell)
{
	t_histo_lst		*history;
	t_histo_lst		*hist_tmp;

	if (!shell->history.lst)
		return ;
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

static void	delete_elem_hist(t_history *hist, t_histo_lst *elem)
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
** Append to the history file
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
	if (!access(path, F_OK) || access(path, X_OK))
		return (free(path));
	if ((fd = open(path, O_WRONLY | O_APPEND)) != -1)
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
