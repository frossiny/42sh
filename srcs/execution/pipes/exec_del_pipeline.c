/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_del_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:34:05 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/17 19:18:32 by alagroy-         ###   ########.fr       */
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
		var_destroy(&(pline->cmd->tenv));
		if (pline->cmd)
			var_destroy(&(pline->cmd->tenv));
		free(pline);
		pline = next;
	}
}
