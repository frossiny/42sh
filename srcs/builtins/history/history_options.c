/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:54:13 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/14 15:27:31 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <fcntl.h>

# include <stdio.h>
/*
** Will parse cmd to add good variable to hist
*/

void	replace_curr_hist(t_cmd *cmd, t_shell *shell)
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
	ft_strdel(&shell->history.lst->str);
	shell->history.lst->str = ret;
}

int		get_index(char **args)
{
	int		i;

	i = 0;
	while (args[i] && !ft_strchr(args[i], '-') && !ft_strchr(args[i], 'd'))
		i++;
	printf("ft_strchr = %s\n", args[i]);
	//if ()
	return (0);
}

void	delone_hist(t_history *hist, char **args)
{
	(void)hist;
	/*size_t		counter;
	t_histo_lst	*history;
	t_histo_lst	*start;

	counter = 0;
	history = hist->lst;
	start = hist->lst;
	if (index > hist->size)
		ft_printf("bash: history: %s: history position out of range", index);
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
	hist->index--;*/
	get_index(args);
}

/*
** Append to the history file
*/

void	append_hist(t_histo_lst *histo)
{
	t_histo_lst	*curr;
	char		*path;
	int			fd;

	if (!histo)
		return ;
	fd = 0;
	path = ft_strpathfile(getenv("HOME"), ".42sh_history");
	if (!access(path, F_OK) || access(path, X_OK))
	{
		free(path);
		return ;
	}
	if ((fd = open(path, O_WRONLY | O_APPEND)))
	{
		if (fd != -1)
		{
			curr = histo;
			while (curr)
			{
				write(fd, curr->str, curr->len);
				write(fd, "\n", 1);
				curr = curr->next;
			}
			close(fd);
		}
	}
	free(path);
}

