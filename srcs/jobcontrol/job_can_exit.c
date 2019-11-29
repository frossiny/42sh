/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_can_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 11:23:26 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/29 11:26:25 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "jobcontrol.h"

int		job_can_exit(void)
{
	t_jobs_lst	*jobs;

	if (!(jobs = g_shell.jobs.lst))
		return (1);
	while (jobs)
	{
		if (ft_strequ(jobs->state, "Stopped"))
			return (0);
		jobs = jobs->next;
	}
	return (1);
}
