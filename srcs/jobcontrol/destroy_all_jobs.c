/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_all_jobs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:38:09 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/19 16:29:00 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	destroy_all_jobs(t_shell *shell)
{
	t_jobs_lst *curr;

	while (shell->jobs->lst)
	{
		curr = shell->jobs->lst;
		shell->jobs->lst = shell->jobs->lst->next;
		free(curr);
	}
	shell->jobs->lst = NULL;
}
