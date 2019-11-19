/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:58:29 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/19 14:49:32 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
# include <stdio.h>

t_jobs	*new_jobs(t_anode *ast)
{
	t_jobs *new_elem;

	if (!(new_elem = malloc(sizeof(t_jobs))))
		return (NULL);
	new_elem->ast = ast;
	new_elem->pid = 0;
	new_elem->status = 0;
	new_elem->prev = NULL; //basic connection, insert it at the right place after
	new_elem->next = (g_shell.jobs) ? g_shell.jobs : NULL; //basic connection
	g_shell.jobs = new_elem;
	return (new_elem);
}
