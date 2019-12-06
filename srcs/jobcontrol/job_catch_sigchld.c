/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_catch_sigchld.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:36:45 by frossiny          #+#    #+#             */
/*   Updated: 2019/12/06 18:10:50 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobcontrol.h"

void	job_catch_sigchld(int signal)
{
	//int			status;
	t_jobs_lst	*job;

	(void)signal;
	//ft_printf("g_Child: %d - CMD: %p\n", g_child, g_shell.current_cmd);
	if (g_child && g_shell.current_cmd)
	{
		//kill(-g_child, SIGTSTP);
		//ppgid = getpgid(ppid);
		//setpgid(mypid, ppgid);
		// tcsetpgrp(g_shell.pgrp, getpgrp());
		job = job_new(g_shell.current_cmd, g_child);
		job->state = "Stopped";
		g_shell.current_cmd = NULL;
		g_child = 0;
	}
}
