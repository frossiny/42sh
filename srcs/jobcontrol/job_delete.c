/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:48:51 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/29 13:38:51 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	update_current_job(t_shell *shell)
{
	if (shell->jobs.len >= 2)
	{
		shell->jobs.last_job->prev->current = '-';
		shell->jobs.minus = shell->jobs.last_job->prev;
	}
	if (shell->jobs.len > 1)
	{
		shell->jobs.plus = shell->jobs.last_job;
		shell->jobs.last_job->current = '+';
	}
}

void	job_free_elem(t_shell *shell, t_jobs_lst *curr)
{
	if (!curr->prev && !curr->next)
	{
		shell->jobs.lst = NULL;
		shell->jobs.last_job = NULL;
		shell->jobs.plus = NULL;
		shell->jobs.minus = NULL;
	}
	if (curr->prev)
		curr->prev->next = curr->next;
	else if (!curr->prev && curr->next)
	{
		shell->jobs.lst = curr->next;
		curr->next->prev = NULL;
	}
	if (!curr->next && curr->prev)
	{
		curr->prev->next = NULL;
		shell->jobs.index--;
		shell->jobs.last_job = curr->prev;
	}
	curr->next ? curr->next->prev = curr->prev : 0;
	free(curr);
	shell->jobs.len--;
	update_current_job(shell);
}

void	job_delete(t_shell *shell, int pid)
{
	t_jobs_lst *curr;

	curr = shell->jobs.lst;
	while (curr)
	{
		if (curr->pid == pid)
		{
			job_free_elem(shell, curr);
			break ;
		}
		curr = curr->next;
	}
}
