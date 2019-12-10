/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 16:51:40 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/10 22:13:37 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "jobcontrol.h"
#include "libft.h"
#include "opt.h"
#include "signal.h"
#include "jobcontrol.h"
#include "shell.h"

int		mark_process_status(pid_t pid, int status)
{
	t_jobs_lst	*plist;
	int			signo;

	if ((plist = job_search(&g_shell, pid)))
	{
		if (WIFSTOPPED(status))
			plist->state = JOB_SUSPENDED;
		else
		{
			plist->state = JOB_COMPLETED;
			if (WIFSIGNALED(status) && (signo = WTERMSIG(status)))
			{
				if (signo != SIGPIPE && signo != SIGINT)
					ft_dprintf(2, "%d\n", signo);
			}
		}
		return (0);
	}
	return (1);
}

int		wait_for_job(int pid)
{
	pid_t	wait;
	int		status;

	while (1)
	{
		if ((wait = waitpid(-pid, &status, WUNTRACED)) == -1)
			return (1);
		if (pid <= 1 || mark_process_status(wait, status)
		|| job_is_stopped(g_shell.jobs.lst)
		|| job_is_completed(g_shell.jobs.lst))
			break ;
	}
	return (0);
}

int		put_foreground(t_shell *shell, int converted, int cont)
{
	t_jobs_lst	*searched;

	searched = job_search(shell, converted);
	if (tcsetpgrp(STDIN_FILENO, searched->pid) < 0)
	{
		perror("Fail to set put pid in foreground");
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", searched->command);
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &searched->tmodes);
		if (kill(-searched->pid, SIGCONT) < 0)
			return (EXIT_FAILURE);
	}
	wait_for_job(searched->pid);
	if (tcsetpgrp(STDIN_FILENO, shell->pid) < 0)
	{
		perror("Failed to put the shell in foreground");
		return (EXIT_FAILURE);
	}
	/* Restore the shell's terminal modes.  */
	if (tcgetattr(STDIN_FILENO, &searched->tmodes) < 0)
		perror("Error 1");
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &shell->prev_term) < 0)
		perror("Error 2");
	job_delete(shell, searched->pid);
	return (EXIT_SUCCESS);
}

int		handle_options_fg(t_shell *shell, t_cmd *cmd)
{
	int converted;

	if (cmd->args[1] && cmd->args[1][0] == '%')
		converted = job_percent(cmd->args[1], "fg");
	else if (cmd->args[1])
		converted = ft_atoi(cmd->args[1]);
	else
		converted = shell->jobs.plus->job_number;
	if (!converted)
		return (1);
	return (put_foreground(shell, converted, 1));
}

int		b_fg(t_cmd *cmd, t_shell *shell)
{
	t_options	*opts;
	int			ret_code;

	ret_code = 0;
	opts = opt_parse(cmd, "", "fg");
	if (opts->ret != 0)
		(opts->ret == -1 ? ft_putendl_fd("fg: usage: fg [job_spec]",
										 2) : 0);
	else
	{
		if (!shell->jobs.lst && !(cmd->argc - opts->last))
			ft_putendl_fd("42sh: fg: current: no such job", 2);
		else if (!shell->jobs.lst && (cmd->argc - opts->last))
			ft_dprintf(2, "42sh: fg: %s: no such job\n", cmd->args[1]);
		else
			ret_code = handle_options_fg(shell, cmd);
	}
	opt_free(opts);
	return (ret_code);
}
