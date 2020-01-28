/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 17:33:11 by alagroy-          #+#    #+#             */
/*   Updated: 2020/01/28 12:50:25 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "shell.h"
#include "libft.h"
#include "structs.h"
#include "expansion.h"

static int		expand_heredoc(t_redirect *redir)
{
	t_token		tok;
	int			i;

	i = -1;
	while (redir->heredoc && redir->heredoc[++i])
	{
		tok.content = ft_strdup(redir->heredoc[i]);
		tok.len = ft_strlen(redir->heredoc[i]);
		tok.type = TOKEN_NAME;
		tok.next = NULL;
		if (!expand(&tok, 0, NULL))
		{
			ft_strdel(&tok.content);
			return (0);
		}
		ft_strdel(&redir->heredoc[i]);
		redir->heredoc[i] = tok.content;
	}
	return (1);
}

static int		read_heredoc(t_redirect *redir)
{
	char	*line;

	g_ignore_signals = 1;
	if (!redir->value->content)
		return (0);
	while (g_ignore_signals && get_input(0, &line, &g_shell))
	{
		if (line && !ft_strcmp(line, redir->value->content))
		{
			ft_strdel(&line);
			break ;
		}
		if (line)
			redir->heredoc = ft_expend_2dstr(redir->heredoc, line);
		ft_strdel(&line);
	}
	g_ignore_signals = 0;
	if (!(expand_heredoc(redir)))
		return (1);
	return (g_clear_buffer);
}

static int		build_heredoc_rec(t_anode *node)
{
	t_redirect	*tmp;

	if (!node)
		return (1);
	if (node->left)
		if (!build_heredoc_rec(node->left))
			return (0);
	if (node->ope && node->right)
		if (!(build_heredoc_rec(node->right)))
			return (0);
	if (node->cmd && node->cmd->redir)
	{
		tmp = node->cmd->redir;
		while (tmp)
		{
			if (tmp->type == TOKEN_REDIRI && tmp->append)
				if (read_heredoc(tmp))
					return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}

int				build_heredoc(t_shell *shell)
{
	if (!(build_heredoc_rec(shell->ast)))
	{
		ast_destroy(shell);
		return (0);
	}
	return (1);
}
