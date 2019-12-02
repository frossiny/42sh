/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_catch_sigstp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:36:45 by frossiny          #+#    #+#             */
/*   Updated: 2019/12/02 11:10:26 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobcontrol.h"

void	job_catch_sigstp(int signal)
{
	t_jobs_lst	*job;

	(void)signal;
	if (g_child && g_shell.current_cmd)
	{
		kill(g_child, 17);
		setpgid(g_child, 0);
		job = job_new(g_shell.current_cmd, g_child);
		job->state = "Stopped";
		g_shell.current_cmd = NULL;
		g_child = 0;
	}
}
