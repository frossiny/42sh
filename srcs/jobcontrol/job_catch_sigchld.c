/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_catch_sigchld.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:36:45 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/11 14:02:29 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobcontrol.h"
#include "execution.h"
#include "ast.h"

static t_jobs_lst	*get_job(int status)
{
	t_jobs_lst	*job;

	(void)status;
	if (g_shell.current_cmd)
	{
		job = job_new(g_shell.current_cmd, g_child);
		job->state = JOB_SUSPENDED;
	}
	else
	{
		if (!(job = job_search_pid(&g_shell, g_child)))
			return (NULL);
		job->state = JOB_SUSPENDED;
		ft_printf("\n[%d]%c  %s                 %s\n", job->job_number,
			job->current, g_jobs_status[job->state], job->command);
	}
	return (job);
}

static void			catch_gchild(void)
{
	pid_t		pid;

	pid = waitpid(g_child, &g_lstatus, WNOHANG | WUNTRACED);
	if (g_shell.current_cmd->exe_found
						&& !WIFEXITED(g_lstatus) && WIFSTOPPED(g_lstatus))
	{
		if (!get_job(g_lstatus))
			return ;
		kill(-g_child, SIGTSTP);
		ast_free_cmd(g_shell.current_cmd);
		g_child = 0;
		g_lstatus = 0;
		tcsetpgrp(g_shell.pgrp, g_shell.pid);
	}
	else
		g_child = 0;
}

void				job_catch_sigchld(int signal)
{
	int			pid;
	int			status;

	(void)signal;
	if (g_child && g_shell.current_cmd)
		catch_gchild();
	else if (!g_child && !g_shell.current_pipel && !g_shell.current_cmd)
	{
		pid = waitpid(0, &status, WNOHANG);
		if (pid > 0)
			job_delete(&g_shell, pid);
	}
}
