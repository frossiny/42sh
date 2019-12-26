/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_catch_sigchld.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:36:45 by frossiny          #+#    #+#             */
/*   Updated: 2019/12/26 17:44:34 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobcontrol.h"

void	job_catch_sigchld(int signal)
{
	t_jobs_lst	*job;

	(void)signal;
	ft_printf("je rentre dans job_catch_sigchld\n");
	if (g_child && g_shell.current_cmd)
	{
		kill(-g_child, SIGTSTP);
		job = job_new(g_shell.current_cmd, g_child);
		job->status = "Stopped";
		job->state = JOB_SUSPENDED;
		g_shell.current_cmd = NULL;
		g_child = 0;
	}
}
