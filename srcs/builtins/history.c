/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:03:36 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/08 17:16:37 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "shell.h"
#include "opt.h"
#include "builtins.h"
#include <fcntl.h>

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

int		print_hist(t_shell *shell, size_t size)
{
	t_histo_lst		*history;
	size_t			counter;

	counter = 0;
	history = shell->history.lst;
	while (history->next && counter != size)
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
** Will read history file and append to history list
*/

void	load_history_file(t_shell *shell)
{
	int		fd;
	char	*path;
	char	*buf;

	fd = 0;
	path = ft_strpathfile(getenv("HOME"), ".42sh_history");
	if (!access(path, F_OK))
		if (access(path, X_OK))
			return ;
	if ((fd = open(path, O_RDONLY)) >= 0)
	{
		while (get_next_line(fd, &buf) == 1)
		{
			add_to_history(buf, &shell->history);
			ft_strdel(&buf);
		}
	}
	free(path);
}

void	loop_history(t_cmd *cmd, t_shell *shell, t_options *opts)
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
			load_history_file(shell);
		else if (!ft_strcmp(opts->opts->opt, "s"))
			parse_and_add_hist(cmd, shell);
		opts->opts = opts->opts->next;
	}
}

/*
** Will print last hist var depending on $HISTSIZE
*/

int		b_history(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;
	t_opt		*tmp_options;

	opts = opt_parse(cmd, "cdanrwps", "history");
	tmp_options = opts->opts;
	if (cmd->argc == 1)
		print_hist(shell, shell->history.histsize);
	else if (ft_strisdigit(cmd->args[1]))
		print_hist(shell, ft_atoi(cmd->args[1]) - 1);
	else
		loop_history(cmd, shell, opts);
	opts->opts = tmp_options;
	opt_free(opts);
	return (0);
}
