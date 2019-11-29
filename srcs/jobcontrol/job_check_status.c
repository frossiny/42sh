/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_check_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:37:47 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/29 16:51:20 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobcontrol.h"

static void	check_pids(t_jobs_lst *job, int *status)
{
	t_childs	*tmp;
	pid_t		cpid;

	if (!job)
		return ;
	if (job->childs)
	{
		tmp = job->childs;
		while (tmp)
		{
			waitpid(tmp->pid, status, WNOHANG);
			tmp = tmp->next;
		}
	}
	else
		waitpid(job->pid, status, WNOHANG);
	while ((cpid = waitpid(-1, NULL, WNOHANG)) > 0)
		;
}

void		job_check_status(void)
{
	t_jobs_lst	*jobs;
	t_jobs_lst	*next;
	int			status;

	if (!(jobs = g_shell.jobs.lst))
		return ;
	while (jobs)
	{
		next = jobs->next;
		check_pids(jobs, &status);
		if (WIFEXITED(status))
		{
			ft_printf("[%d]%c Done %s\n",
				jobs->job_number, jobs->current, jobs->command);
			job_delete(&g_shell, jobs->pid);
		}
		jobs = next;
	}
}
