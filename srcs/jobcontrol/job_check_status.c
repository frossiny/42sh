/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_check_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:37:47 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/14 14:45:19 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobcontrol.h"

static int	check_pids(t_jobs_lst *job, int *status)
{
	t_pipel		*tmp;
	int			ret;

	if (!job)
		return (0);
	if (job->pipeline)
	{
		ret = 0;
		tmp = job->pipeline;
		while (tmp)
		{
			if (waitpid(tmp->pid, status, WNOHANG) == 0)
				ret = 1;
			tmp = tmp->next;
		}
		return (ret);
	}
	return (waitpid(job->pid, status, WNOHANG) != 0);
}

static void	remove_ghosts(void)
{
	pid_t		cpid;

	while ((cpid = waitpid(-1, NULL, WNOHANG)) > 0)
		;
}

void		job_check_status(void)
{
	t_jobs_lst	*jobs;
	t_jobs_lst	*next;
	int			status;

	if (!(jobs = g_shell.jobs.lst))
		return (remove_ghosts());
	status = 0;
	while (jobs)
	{
		next = jobs->next;
		if (check_pids(jobs, &status) && WIFEXITED(status))
		{
			isatty(0) && !jobs->foreground ? ft_printf("[%d]%c Done %s\n",
				jobs->job_number, jobs->current, jobs->command) : 0;
			job_delete(&g_shell, jobs->pid);
		}
		jobs = next;
	}
	remove_ghosts();
}
