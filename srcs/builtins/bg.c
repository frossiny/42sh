/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:32:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/06 15:08:03 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "jobcontrol.h"
#include "builtins.h"
#include "opt.h"
#include "signal.h"
# include <stdio.h>

int		set_bg(t_shell *shell, int converted, int cont)
{
	t_jobs_lst *searched;

	(void)cont;
	searched = job_search(shell, converted);
	ft_printf("[%d]%c %s\n", searched->job_number, searched->current,
	searched->command);
	searched->state = "Running";
	if (kill(-searched->pid, SIGCONT) < 0)
		return (EXIT_FAILURE);
	return (0);
}

int		handle_options_bg(t_shell *shell, t_cmd *cmd)
{
	int converted;

	if (cmd->args[1] && cmd->args[1][0] == '%')
		converted = job_percent(cmd->args[1], "bg");
	else if (cmd->args[1])
		converted = ft_atoi(cmd->args[1]);
	else
		converted = shell->jobs.plus->job_number;
	if (!converted)
		return (1);
	return (set_bg(shell, converted, 1));
}

int		b_bg(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;

	opts = opt_parse(cmd, "", "bg");
	if (opts->ret != 0)
		(opts->ret == -1 ? ft_putendl_fd("bg: usage: bg [job_spec]",
		2) : 0);
	else
	{
		if (!shell->jobs.lst && !(cmd->argc - opts->last))
			ft_putendl_fd("42sh: bg: current: no such job", 2);
		else if (!shell->jobs.lst && (cmd->argc - opts->last))
			ft_dprintf(2, "42sh: bg: %s: no such job\n", cmd->args[1]);
		else
			handle_options_bg(shell, cmd);
	}
	opt_free(opts);
	return (0);
}
