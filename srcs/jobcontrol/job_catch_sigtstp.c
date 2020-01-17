/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_catch_sigtstp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:12:26 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/17 16:43:42 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "jobcontrol.h"
#include "shell.h"

void	job_catch_sigtstp(int signal)
{
	t_jobs_lst	*job;

	(void)signal;
	if (!g_shell.current_pipel)
		return ;
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
