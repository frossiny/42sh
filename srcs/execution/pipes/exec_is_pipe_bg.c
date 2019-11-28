/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_is_pipe_bg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 13:31:42 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/28 15:08:20 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int		exec_is_pipe_bg(t_pipel *pipeline)
{
	if (!pipeline)
		return (0);
	while (pipeline->next)
		pipeline = pipeline->next;
	return (pipeline->cmd && pipeline->cmd->is_bg);
}
