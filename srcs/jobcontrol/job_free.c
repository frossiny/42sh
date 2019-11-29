/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:15:50 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/28 15:18:24 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	job_free(t_jobs_lst *job)
{
	if (!job)
		return ;
	if (job->childs)
		exec_child_del(job->childs);
	free(job->command);
	free(job);
}
