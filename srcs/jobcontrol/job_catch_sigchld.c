/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_catch_sigchld.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:36:45 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/20 18:38:17 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobcontrol.h"
#include "execution.h"

static void	catch_gchild(void)
{
	t_jobs_lst	*job;
	int			pid;

	pid = waitpid(g_child, &g_lstatus, WNOHANG);
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
		tcsetpgrp(g_shell.pgrp, g_shell.pid);
		ft_printf("\n[%d]%c  %s                 %s\n", job->job_number,
		job->current, job->status, job->command);
	}
	else
		g_child = 0;
}

void		job_catch_sigchld(int signal)
{
	int			pid;
	int			status;

	(void)signal;
	if (g_child)
		catch_gchild();
	else if (!g_shell.current_pipel)
	{
		pid = waitpid(0, &status, WNOHANG);
		if (pid > 0)
			job_delete(&g_shell, pid);
	}
}
