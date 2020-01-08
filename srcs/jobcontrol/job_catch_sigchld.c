/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_catch_sigchld.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:36:45 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/07 12:55:34 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobcontrol.h"

void	job_catch_sigchld(int signal)
{
	t_jobs_lst	*job;
	int			pid;
	int			status;

	(void)signal;
	if (g_child && g_shell.current_cmd)
	{
		pid = waitpid(g_child, &status, WNOHANG);
		if (pid == 0)
		{
			kill(-g_child, SIGTSTP);
			job = job_new(g_shell.current_cmd, g_child);
			job->status = "Stopped";
			job->state = JOB_SUSPENDED;
			g_shell.current_cmd = NULL;
			g_child = 0;
		}
		else
		{
			g_last_status = status;
			g_child = 0;
		}
	}
}
