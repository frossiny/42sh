/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:32:46 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/15 17:28:09 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "jobcontrol.h"
#include "execution.h"
#include "builtins.h"
#include "opt.h"
#include "signal.h"

/*
** Send SIGCONT signal, and continue background stopped processes
*/

int		set_bg(t_shell *shell, int converted, int cont)
{
	t_jobs_lst *searched;

	searched = job_search(shell, converted);
	if (searched->state == JOB_RUNNING)
	{
		ft_dprintf(2, "42sh: bg: job %d already in background\n",
		searched->job_number);
		return (0);
	}
	ft_printf("[%d]%c %s\n", searched->job_number, searched->current,
	searched->command);
	if (searched->state == JOB_SUSPENDED)
		searched->state = JOB_CONTINUED;
	searched->status = "Running";
	if (cont)
	{
		if (!searched->pipeline)
		{
			if (kill(-searched->pid, SIGCONT) < 0)
				return (EXIT_FAILURE);
		}
		else
			exec_signal_pipe(searched->pipeline, SIGCONT);
	}
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

/*
** builtin bg, handle options
*/

int		b_bg(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;
	int			ret_code;

	ret_code = 0;
	opts = opt_parse(cmd, "", "bg");
	if (opts->ret != 0)
		(opts->ret == -1 ? ft_putendl_fd("bg: usage: bg [job_spec]",
		2) : 0);
	else
	{
		if (!shell->jobs.lst && !(cmd->argc - opts->last))
		{
			ft_putendl_fd("42sh: bg: current: no such job", 2);
			return (1);
		}
		else if (!shell->jobs.lst && (cmd->argc - opts->last))
		{
			ft_dprintf(2, "42sh: bg: %s: no such job\n", cmd->args[1]);
			return (1);
		}
		else
			ret_code = handle_options_bg(shell, cmd);
	}
	opt_free(opts);
	return (ret_code);
}
