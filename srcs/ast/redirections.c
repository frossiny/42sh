/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:11:08 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/14 16:20:30 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "ast.h"
#include "utils.h"
#include "lexer.h"

static int			is_append(t_token *token)
{
	if (token->type == TOKEN_REDIRI)
		return (ft_strstr(token->content, "<<") != NULL);
	else if (token->type == TOKEN_REDIRO)
		return (ft_strstr(token->content, ">>") != NULL);
	else
		return (0);
}

static t_redirect	*create_redirection(t_token *token)
{
	t_redirect	*red;

	if (!token || !(red = (t_redirect *)malloc(sizeof(t_redirect))))
		return (NULL);
	red->done = 0;
	if (token->type == TOKEN_IO_FD)
	{
		red->filedes = ft_atoi(token->content);
		token = token->next;
	}
	else
	{
		if (token->type != TOKEN_AGGR)
			red->filedes = (token->type == TOKEN_REDIRO) ? 1 : 0;
		else
			red->filedes = (ft_strstr(token->content, ">&")) ? 1 : 0;
	}
	red->type = token->type;
	red->append = is_append(token);
	red->value = token->next;
	red->next = NULL;
	red->heredoc = NULL;
	return (red);
}

static t_redirect	*add_red(t_redirect **redir, t_token *tok)
{
	t_redirect	*curr;

	if (!redir)
		return (NULL);
	if (!*redir)
		*redir = create_redirection(tok);
	else
	{
		curr = *redir;
		while (curr->next)
			curr = curr->next;
		curr->next = create_redirection(tok);
	}
	return (*redir);
}

t_redirect			*parse_redirections(t_token *tok)
{
	t_redirect	*red;

	if (!tok || !tok->next)
		return (NULL);
	red = NULL;
	while (tok_is_cmd_comp(tok))
	{
		if (tok_is_redirection(tok))
		{
			add_red(&red, tok);
			tok = tok->next->next;
		}
		else
			tok = tok->next;
	}
	return (red);
}

int					validate_redirection(t_redirect *redir)
{
	while (redir)
	{
		if (redir->type == TOKEN_REDIRI && redir->append == 0)
		{
			if (!u_file_exists(redir->value ? redir->value->content : NULL, 1))
				return (0);
			if (!u_file_can_read(redir->value ? redir->value->content : NULL))
				return (0);
		}
		if (redir->type == TOKEN_REDIRO)
		{
			if (!u_file_can_write(redir->value ? redir->value->content : NULL))
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}
