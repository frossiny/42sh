/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:55:54 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/08 14:15:36 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

/*
** Search elem via pid in job control linked list
*/

t_jobs_lst	*job_search(t_shell *shell, int job_number)
{
	t_jobs_lst *jobs;

	jobs = shell->jobs.lst;
	while (jobs)
	{
		if (job_number == jobs->job_number)
			return (jobs);
		jobs = jobs->next;
	}
	return (NULL);
}

t_jobs_lst	*job_search_pid(t_shell *shell, int pid)
{
	t_jobs_lst *jobs;

	jobs = shell->jobs.lst;
	while (jobs)
	{
		if (pid == jobs->pid)
			return (jobs);
		jobs = jobs->next;
	}
	return (NULL);
}
