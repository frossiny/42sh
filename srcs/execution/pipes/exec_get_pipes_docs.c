/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_pipes_docs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 18:45:40 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/28 11:41:21 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int		exec_get_pipes_docs(t_shell *shell, t_pipel *pipes)
{
	while (pipes && pipes->cmd)
	{
		if (!get_here_doc(pipes->cmd->redir, shell))
			return (0);
		if (!pipes->next)
			break ;
		pipes = pipes->next;
	}
	return (1);
}
