/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_destroy_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:49:02 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/27 18:20:11 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	jobs_destroy_all(t_shell *shell)
{
	t_jobs_lst *curr;

	while (shell->jobs.lst)
	{
		curr = shell->jobs.lst;
		shell->jobs.lst = shell->jobs.lst->next;
		free(curr);
	}
	shell->jobs.lst = NULL;
}
