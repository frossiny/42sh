/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:03:36 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/07 22:18:05 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "opt.h"
#include <fcntl.h>
# include <stdio.h>

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
		ft_strdel(&history->str);
		free(history);
		history = NULL;
	}
	shell->history.index = 1;
	shell->history.lst = NULL;
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
	if (!access(path, F_OK))
		if (access(path, X_OK))
			return ;
	if (fd != -1)
		if ((fd = open(path, O_WRONLY | O_APPEND)))
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
	free(path);
}

int		print_hist(t_shell *shell)
{
	t_histo_lst		*history;
	size_t			counter;

	counter = 0;
	history = shell->history.lst;
	while (history->next && counter != shell->history.histsize)
	{
		history = history->next;
		counter++;
	}
	while (history)
	{
		ft_printf("  %2zu  %s\n", history->index, history->str);
		history = history->prev;
	}
	return (0);
}

/*
** Will parse cmd to add good variable to hist
*/

void	parse_and_add_hist(t_cmd *cmd, t_shell *shell)
{
	int		i;
	int		e;
	int		k;
	char	*ret;

	(void)shell;
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
	shell->history.lst->str = ret;
}

/*
** Will print last hist var depending on $HISTSIZE
*/

int		b_history(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;

	opts = opt_parse(cmd, "cdanrwps", "history");
	if (cmd->argc == 1)
		print_hist(shell);
	else
	{
		while (opts->opts)
		{
			if (!ft_strcmp(opts->opts->opt, "c"))
				empty_hist(shell);
			else if (!ft_strcmp(opts->opts->opt, "w"))
				overwrite_history(shell->history.lst);
			else if (!ft_strcmp(opts->opts->opt, "a"))
				append_hist(shell->history.lst);
			else if (!ft_strcmp(opts->opts->opt, "r"))
				shell->history = get_history();
			else if (!ft_strcmp(opts->opts->opt, "s"))
				parse_and_add_hist(cmd, shell);
			opts->opts = opts->opts->next;
		}
	}
	opt_free(opts);
	return (0);
}
