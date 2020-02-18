/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 16:51:40 by lubenard          #+#    #+#             */
/*   Updated: 2020/02/14 14:08:26 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "jobcontrol.h"
#include "libft.h"
#include "opt.h"
#include "signal.h"
#include "jobcontrol.h"
#include "shell.h"
#include "execution.h"

/*
** Set new status to processes when waiting for them
*/

int		mark_process_status(t_jobs_lst *job, int status)
{
	int			signo;

	if (!job)
		return (WEXITSTATUS(status));
	if (WIFSTOPPED(status))
		job->state = JOB_SUSPENDED;
	else
	{
		job->state = JOB_COMPLETED;
		if (WIFSIGNALED(status) && (signo = WTERMSIG(status)))
			display_signal(signo);
	}
	return (WEXITSTATUS(status));
}

/*
** Wait for job to complete
*/

int		wait_for_job(t_jobs_lst *job)
{
	int		status;

	g_child = job->pid;
	if (waitpid(-job->pid, &status, WUNTRACED) == -1)
		return (-1);
	return (mark_process_status(job, status));
}

/*
** shell prev_term seems to change between shell init and fg command
** set bg process into foreground then restore shell into foreground
*/

int		put_foreground(t_jobs_lst *searched, int cont)
{
	if (!searched->pipeline && tcsetpgrp(g_shell.pgrp, searched->pid) < 0)
		return (EXIT_FAILURE);
	ft_printf("%s\n", searched->command);
	if (cont)
	{
		restore_shell(g_shell.prev_term);
		if (!searched->pipeline && kill(-searched->pid, SIGCONT) < 0)
			return (EXIT_FAILURE);
		searched->pipeline ? exec_signal_pipe(searched->pipeline, SIGCONT) : 0;
	}
	searched->state = JOB_RUNNING;
	searched->foreground = 1;
	g_return = wait_for_job(searched);
	tcsetpgrp(g_shell.pgrp, g_shell.pid);
	termcaps_init(NULL);
	if (job_is_completed(searched))
		job_delete(&g_shell, searched->pid);
	else
	{
		searched->state = JOB_SUSPENDED;
		ft_printf("[%d]%c %s %s\n", searched->job_number, searched->current,
					g_jobs_status[searched->state], searched->command);
	}
	return (g_return);
}

int		handle_options_fg(t_cmd *cmd)
{
	int			converted;
	t_jobs_lst	*searched;

	if (cmd->args[1] && cmd->args[1][0] == '%')
		converted = job_percent(cmd->args[1], "fg");
	else if (cmd->args[1])
		converted = ft_atoi(cmd->args[1]);
	else
		converted = g_shell.jobs.plus->job_number;
	if (!converted)
		return (1);
	if (!(searched = job_search(&g_shell, converted)))
	{
		ft_dprintf(2, "42sh: fg: %%%d: no such job\n", converted);
		return (1);
	}
	if (!searched)
		return (EXIT_FAILURE);
	return (put_foreground(searched, 1));
}

int		b_fg(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;
	int			ret_code;

	ret_code = 0;
	opts = opt_parse(cmd, "", "fg");
	if (opts->ret != 0)
		(opts->ret == -1 ? ft_putendl_fd("fg: usage: fg [job_id]", 2) : 0);
	else
	{
		if (!shell->jobs.lst && !(cmd->argc - opts->last))
		{
			ft_putendl_fd("42sh: fg: current: no such job", 2);
			ret_code = 1;
		}
		else
			ret_code = handle_options_fg(cmd);
	}
	opt_free(opts);
	return (ret_code);
}
