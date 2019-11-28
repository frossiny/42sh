/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_check_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:37:47 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/28 12:01:32 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobcontrol.h"

/* static void debug(void)
{
	t_jobs_lst	*jobs = g_shell.jobs.lst;
	while (jobs)
	{
		ft_printf("Still running: [%d] %d %s\n",
			jobs->job_number, jobs->pid, jobs->command);
		jobs = jobs->next;
	}
}*/

void	job_check_status(void)
{
	t_jobs_lst	*jobs;
	t_jobs_lst	*next;
	int			status;

	if (!(jobs = g_shell.jobs.lst))
		return ;
	// debug();
	while (jobs)
	{
		next = jobs->next;
		waitpid(jobs->pid, &status, WNOHANG);
		if (WIFEXITED(status))
		{
			ft_printf("[%d]%c Done %s\n",
				jobs->job_number, jobs->current, jobs->command);
			waitpid(jobs->pid, &status, 0);
			job_delete(&g_shell, jobs->pid);
		}
		jobs = next;
	}
}
