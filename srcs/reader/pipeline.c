/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:28:42 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 18:40:35 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "shell.h"
#include "ast.h"
#include "builtins.h"

static t_pipel	*create_pipel(t_pipel *prev, t_cmd *cmd, t_shell *shell)
{
	t_pipel		*new;

	if (!cmd || !(new = (t_pipel *)malloc(sizeof(t_pipel))))
		return (NULL);
	if (build_args(cmd, shell->vars) == -1)
		return (NULL);
	cmd->redir = parse_redirections(cmd->exe, cmd->argc);
	new->cmd = cmd;
	new->previous = prev;
	new->next = NULL;
	return (new);
}

static void		init_redirect_output(t_redirect *redir)
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

t_pipel			*build_pipeline(t_anode *node, t_shell *shell, t_anode **cn)
{
	t_pipel	*pipel;
	t_pipel *curr;

	if (!node || !cn || !(pipel = create_pipel(NULL, node->cmd, shell)))
		return (NULL);
	curr = pipel;
	node = node->parent;
	while (node && node->ope)
	{
		if (!(curr->next = create_pipel(curr, node->right->cmd, shell)))
			break ;
		curr = curr->next;
		init_redirect_output(curr->cmd->redir);
		node = node->parent;
	}
	*cn = node ? node->left : node;
	return (pipel);
}

void			del_pipeline(t_pipel *pline)
{
	t_pipel		*next;

	while (pline && pline->previous)
		pline = pline->previous;
	while (pline)
	{
		next = pline->next;
		close_here_docs(pline->cmd->redir);
		free(pline);
		pline = next;
	}
}
