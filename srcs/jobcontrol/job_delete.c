/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:48:51 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/27 17:01:02 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	job_delete(t_shell *shell, int pid)
{
	t_jobs_lst *jobs;
	t_jobs_lst *to_delete;

	jobs = shell->jobs->lst;
	while (jobs)
	{
		if (pid == jobs->pid)
		{
			to_delete = jobs;
			if (prev)
			{
				jobs->prev->next = jobs->next;
				jobs->next->prev = jobs->prev;
			}
			else
			{
				shell->jobs->lst = jobs->next;
				shell->jobs->lst->prev = NULL;
			}
			free(to_delete);
			break ;
		}
		jobs = jobs->next;
	}
}
