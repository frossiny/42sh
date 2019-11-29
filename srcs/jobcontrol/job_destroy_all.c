/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_destroy_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:49:02 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/29 13:17:35 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	jobs_destroy_all(t_shell *shell)
{
	t_jobs_lst *curr;

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
