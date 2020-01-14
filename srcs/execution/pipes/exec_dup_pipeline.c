/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:04:52 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/14 17:39:09 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "shell.h"

t_pipel		*dup_one(t_pipel *pipel, t_pipel *prev)
{
	t_pipel		*new;

	if (!(new = (t_pipel *)malloc(sizeof(t_pipel))))
		return (NULL);
	new->previous = prev;
	new->pid = pipel->pid;
	new->cmd = NULL;
	new->next = NULL;
	return (new);
}

t_pipel		*exec_dup_pipeline(t_pipel *src)
{
	t_pipel		*new;
	t_pipel		*curr;
	t_pipel		*tmp;

	if (!(curr = dup_one(src, NULL)))
		return (NULL);
	new = curr;
	src = src->next;
	while (src)
	{
		tmp = dup_one(src, curr);
		curr->next = tmp;
		curr = tmp;
		src = src->next;
	}
	return (new);
}
