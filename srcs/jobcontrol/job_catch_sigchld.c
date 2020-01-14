/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_catch_sigchld.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:36:45 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/14 17:55:28 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobcontrol.h"
#include "execution.h"

static void	job_pipe_stop(void)
{
	t_jobs_lst	*job;
	t_pipel		*pipe;
	int			status;
	pid_t		pid;

	if (!(pipe = g_shell.current_pipel))
		return ;
	while (pipe)
	{
		pid = waitpid(pipe->pid, &status, WNOHANG);
		if (pid == 0)
		{
			exec_signal_pipe(g_shell.current_pipel, SIGTSTP);
			if (g_shell.current_pipel)
				job = job_new_pipe(g_shell.current_pipel);
			else
			{
				if (!(job = job_search_pid(&g_shell, g_child)))
					return ;
			}
			job->status = "Stopped";
			job->state = JOB_SUSPENDED;
			g_shell.current_pipel = NULL;
			tcsetpgrp(g_shell.pgrp, getpgrp());
		}
	}
}

void		job_catch_sigchld(int signal)
{
	t_jobs_lst	*job;
	int			pid;
	int			status;

	(void)signal;
	if (g_child)
	{
		pid = waitpid(g_child, &status, WNOHANG);
		if (pid == 0)
		{
			kill(-g_child, SIGTSTP);
			if (g_shell.current_cmd)
				job = job_new(g_shell.current_cmd, g_child);
			else
			{
				if (!(job = job_search_pid(&g_shell, g_child)))
					return ;
			}
			job->status = "Stopped";
			job->state = JOB_SUSPENDED;
			g_shell.current_cmd = NULL;
			g_child = 0;
			tcsetpgrp(g_shell.pgrp, getpgrp());
		}
		else
		{
			g_last_status = status;
			g_child = 0;
		}
	}
	else if (g_shell.current_pipel)
		job_pipe_stop();
	else
	{
		pid = waitpid(0, &status, WNOHANG);
		if (pid > 0)
			job_delete(&g_shell, pid);
	}
}
