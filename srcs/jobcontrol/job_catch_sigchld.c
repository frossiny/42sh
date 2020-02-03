/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_catch_sigchld.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:36:45 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/31 18:05:03 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobcontrol.h"
#include "execution.h"
#include "ast.h"

static void	catch_gchild(void)
{
	t_jobs_lst	*job;
	int			pid;

	pid = waitpid(g_child, &g_lstatus, WNOHANG | WUNTRACED);
	if (g_shell.current_cmd->exe_found && WIFSTOPPED(g_lstatus))
	{
		kill(-g_child, SIGTSTP);
		if (g_shell.current_cmd)
			job = job_new(g_shell.current_cmd, g_child);
		else
		{
			if (!(job = job_search_pid(&g_shell, g_child)))
				return ;
			job->state = JOB_SUSPENDED;
			ft_printf("\n[%d]%c  %s                 %s\n", job->job_number,
				job->current, g_jobs_status[job->state], job->command);
		}
		job->state = JOB_SUSPENDED;
		ast_free_cmd(g_shell.current_cmd);
		g_child = 0;
		g_lstatus = 0;
		tcsetpgrp(g_shell.pgrp, g_shell.pid);
	}
	else
		g_child = 0;
}

void		job_catch_sigchld(int signal)
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
