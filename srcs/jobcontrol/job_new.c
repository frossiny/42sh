/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:48:31 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/28 13:41:13 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobcontrol.h"

static void		jobs_insert(t_jobs_lst *job)
{
	t_jobs_lst	*curr;

	curr = g_shell.jobs.lst;
	if (!curr)
		g_shell.jobs.lst = job;
	else
	{
		while (curr->next)
			curr = curr->next;
		job->prev = curr;
		job->next = NULL;
		curr->next = job;
	}
	if (g_shell.jobs.index > 3)
		g_shell.jobs.last_job->prev->current = ' ';
	if (g_shell.jobs.index > 2)
	{
		g_shell.jobs.minus = g_shell.jobs.last_job;
		g_shell.jobs.last_job->current = '-';
	}
	if (g_shell.jobs.index == 2)
		g_shell.jobs.minus = job;
	g_shell.jobs.last_job = job;
	g_shell.jobs.plus = job;
}

t_jobs_lst		*job_new(t_cmd *cmd)
{
	t_jobs_lst *job;

	if (!(job = (t_jobs_lst *)malloc(sizeof(t_jobs_lst))))
		return (NULL);
	job->command = job_get_command(cmd);
	job->job_number = g_shell.jobs.index++;
	job->pid = 0;
	job->current = '+';
	job->state = "Undefinited_status";
	job->prev = NULL;
	job->next = NULL;
	jobs_insert(job);
	return (job);
}
