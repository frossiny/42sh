/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_del_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:34:05 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/20 10:59:57 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"
#include "execution.h"

void	exec_del_pipeline(t_pipel *pline)
{
	t_pipel		*next;

	while (pline && pline->previous)
		pline = pline->previous;
	while (pline)
	{
		next = pline->next;
		pline->cmd ? var_destroy(&(pline->cmd->tenv)) : 0;
		if (pline->cmd)
			var_destroy(&(pline->cmd->tenv));
		free(pline);
		pline = next;
	}
}
