/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:15:50 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/14 14:43:59 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	job_free(t_jobs_lst *job)
{
	if (!job)
		return ;
	if (job->pipeline)
		exec_del_pipeline(job->pipeline);
	free(job->command);
	free(job);
}
