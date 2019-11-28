/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:28:42 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/28 15:37:19 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "shell.h"
#include "execution.h"
#include "ast.h"
#include "builtins.h"

static void	init_redirect_output(t_redirect *redir)
{
	int		fd;
	int		otype;

	if (!redir || redir->type == TOKEN_REDIRI || redir->type == TOKEN_AGGR)
		return ;
	otype = O_RDONLY | O_CREAT | O_APPEND;
	if ((fd = open(redir->value->content, otype, 420)) == -1)
		return ;
	close(fd);
}

t_pipel		*exec_build_pipeline(t_anode *node, t_shell *shell, t_anode **cn)
{
	t_pipel	*pipel;
	t_pipel *curr;

	if (!node || !cn || !(pipel = exec_pipeline_alloc(NULL, node->cmd, shell)))
		return (NULL);
	curr = pipel;
	node = node->parent;
	while (node && node->ope)
	{
		if (!(curr->next = exec_pipeline_alloc(curr, node->right->cmd, shell)))
			break ;
		curr = curr->next;
		init_redirect_output(curr->cmd->redir);
		node = node->parent;
	}
	*cn = node ? node->left : node;
	return (pipel);
}
