/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:03:36 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/19 14:15:31 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "shell.h"
#include "opt.h"
#include "builtins.h"
#include "history.h"
#include <fcntl.h>

/*
** Will read history file and append to history list
*/

void		load_history_file(t_shell *shell)
{
	int		fd;
	char	*path;
	char	*buf;

	fd = 0;
	path = ft_strpathfile(getenv("HOME"), ".42sh_history");
	if (!access(path, F_OK) && access(path, X_OK))
		return (free(path));
	if ((fd = open(path, O_RDONLY)) >= 0)
		while (get_next_line(fd, &buf) == 1)
		{
			if (ft_strisascii(buf) && ft_strcmp(buf, ""))
				add_to_history(buf, &shell->history);
			ft_strdel(&buf);
		}
	close(fd);
	free(path);
}

int			verify_options_hist(t_opt *opts)
{
	size_t is_set;

	is_set = 0;
	while (opts)
	{
		if (!ft_strcmp(opts->opt, "w"))
			is_set++;
		else if (!ft_strcmp(opts->opt, "a"))
			is_set++;
		else if (!ft_strcmp(opts->opt, "r"))
			is_set++;
		if (is_set > 1)
		{
			ft_putendl_fd("42sh: history: cannot use more than one of -arw", 2);
			return (0);
		}
		opts = opts->next;
	}
	return (1);
}

/*
** Check options for history
*/

int			loop_history(t_cmd *cmd, t_shell *shell, t_options *opts)
{
	while (opts->opts)
	{
		if (!ft_strcmp(opts->opts->opt, "d"))
			return (delone_hist(&shell->history, opts->opts->value));
		if (!ft_strcmp(opts->opts->opt, "c"))
			empty_hist(shell);
		else if (!ft_strcmp(opts->opts->opt, "w"))
			overwrite_history(shell->history.lst);
		else if (!ft_strcmp(opts->opts->opt, "a"))
			append_hist(shell->history.lst);
		else if (!ft_strcmp(opts->opts->opt, "r"))
			load_history_file(shell);
		else if (!ft_strcmp(opts->opts->opt, "s"))
			replace_curr_hist(cmd, shell);
		opts->opts = opts->opts->next;
	}
	return (0);
}

static int	execute_hist(t_cmd *cmd, t_shell *shell, t_options *opts)
{
	int			ret;

	ret = 0;
	if (opts->ret != 0)
	{
		(opts->ret == -1 ? ft_putendl_fd("42sh: history: usage: \
						[-c] [-d offset] or history -awrn", 2) : 0);
		ret = 2;
	}
	else if (cmd->argc == 1)
		print_hist(shell, shell->history.histsize);
	else if (cmd->args[1][0] == '-')
		ret = loop_history(cmd, shell, opts);
	else if (ft_strisdigit(cmd->args[1]))
		print_hist(shell, ft_atoi(cmd->args[1]));
	else
	{
		ft_dprintf(2, "42sh: history: %s: numeric argument required\n",
															cmd->args[1]);
		ret = 1;
	}
	return (ret);
}

int			b_history(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;
	t_opt		*tmp_options;
	int			ret;

	ret = 0;
	opts = opt_parse(cmd, "cd:arws", "history");
	tmp_options = opts->opts;
	if (!verify_options_hist(opts->opts))
		return (1);
	ret = execute_hist(cmd, shell, opts);
	opts->opts = tmp_options;
	opt_free(opts);
	return (ret);
}
