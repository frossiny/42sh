/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_destroy_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:49:02 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/29 17:50:43 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execution.h"

static void	kill_jobs(t_shell *shell)
{
	t_jobs_lst	*jobs;

	jobs = shell->jobs.lst;
	while (jobs)
	{
		if (ft_strequ(jobs->state, "Stopped"))
			kill(jobs->pid, SIGCONT);
		kill(jobs->pid, SIGHUP);
		jobs = jobs->next;
	}
}

/*
**	Use only on shell exit
*/
void		jobs_destroy_all(t_shell *shell, int kill)
{
	t_jobs_lst *curr;

	kill ? kill_jobs(shell) : 0;
	while (shell->jobs.lst)
	{
		curr = shell->jobs.lst;
		shell->jobs.lst = shell->jobs.lst->next;
		exec_child_del(curr->childs);
		free(curr);
	}
	shell->jobs.lst = NULL;
	shell->jobs.minus = NULL;
	shell->jobs.plus = NULL;
	shell->jobs.last_job = NULL;
	shell->jobs.index = 1;
	shell->jobs.len = 1;
}
