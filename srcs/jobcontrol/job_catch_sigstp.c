/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_catch_sigstp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:36:45 by frossiny          #+#    #+#             */
/*   Updated: 2019/12/03 17:59:29 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobcontrol.h"
# include <errno.h>

/*
** Setpgid fails because it returns Pemission denied (EACESS)
** Why ? Because we already executed execve.
** See man of setpgid
*/

void	job_catch_sigstp(int signal)
{
	t_jobs_lst	*job;

	(void)signal;
	if (g_child && g_shell.current_cmd)
	{
		kill(-g_child, 17);
		ft_printf("g_child = %d\n", g_child);
		if (setpgid(g_child, 0) < 0)
			perror("setpgid failed");
		job = job_new(g_shell.current_cmd, g_child);
		job->state = "Stopped";
		g_shell.current_cmd = NULL;
		g_child = 0;
	}
}
