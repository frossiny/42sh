/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_all_jobs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:38:09 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/19 14:53:11 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	destroy_all_jobs(t_shell *shell)
{
	t_jobs *curr;

	while (shell->jobs)
	{
		curr = shell->jobs;
		shell->jobs = shell->jobs->next;
		free(curr);
	}
	shell->jobs = NULL;
}
