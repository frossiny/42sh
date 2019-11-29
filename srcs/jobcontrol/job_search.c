/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:55:54 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/28 18:05:18 by lubenard         ###   ########.fr       */
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
