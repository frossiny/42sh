/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:25:57 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/19 14:38:40 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	delete_job(t_shell *shell, size_t pid)
{
	t_jobs *jobs;
	t_jobs *to_delete;

	jobs = shell->jobs;
	while (jobs)
	{
		if (pid == jobs->next->pid)
		{
			to_delete = jobs->next;
			jobs->next = jobs->next->next;
			free(to_delete);
			break ;
		}
		jobs = jobs->next;
	}
}
