/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:48:51 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/27 18:49:09 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	job_delete(t_shell *shell, int pid)
{
	t_jobs_lst *curr;
	t_jobs_lst *prev;
	t_jobs_lst *next;

	curr = shell->jobs.lst;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		if (curr->pid == pid)
		{
			if (prev)
				prev->next = next;
			else
				shell->jobs.lst = next;
			if (shell->jobs.last_job == curr)
				shell->jobs.last_job = NULL;
			free(curr);
			break ;
		}
		curr = next;
	}
}
