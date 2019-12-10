/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 17:25:35 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/10 15:47:58 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "jobcontrol.h"

/*
** Return true if all process in the job have stopped
** or completed
*/

int		job_is_stopped(t_jobs_lst *jobs)
{
	while (jobs)
	{
		if (jobs->state != JOB_COMPLETED && jobs->state != JOB_SUSPENDED)
			return (0);
		jobs = jobs->next;
	}
	return (1);
}

int		job_is_completed(t_jobs_lst *jobs)
{
	while (jobs)
	{
		if (jobs->state != JOB_COMPLETED)
			return (0);
		jobs = jobs->next;
	}
	return (1);
}
