/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:52:54 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/29 15:18:41 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"
#include "ast.h"

static t_token	*get_cmd_end(t_token *tok)
{
	while (tok)
	{
		if (tok_is_word(tok))
			tok = tok->next;
		else if (tok->type == TOKEN_ASSIGNMENT)
			tok = tok->next;
		else if (tok->type == TOKEN_IO_FD)
			tok = tok->next;
		else if (tok->type == TOKEN_REDIRO || tok->type == TOKEN_REDIRI)
			tok = tok->next;
		else if (tok->type == TOKEN_AGGR)
			tok = tok->next;
		else if (tok->type == TOKEN_JOBS)
		{
			tok = tok->next;
			break ;
		}
		else
			break ;
	}
	return (tok);
}

t_anode			*create_cond_node(t_token **tokens)
{
	t_token	*tok;
	t_anode	*node;
	t_anode	*new;
	t_anode *ncmd;

	node = ast_create_node(NULL, create_cmd(*tokens));
	tok = get_cmd_end(*tokens);
	if (!tok || tok->type != TOKEN_PIPE)
	{
		*tokens = tok;
		return (node);
	}
	while (tok && tok->type == TOKEN_PIPE)
	{
		new = ast_create_node(tok, NULL);
		new->left = node;
		tok = tok->next;
		ncmd = ast_create_node(NULL, create_cmd(tok));
		ncmd->parent = new;
		new->right = ncmd;
		node->parent = new;
		node = new;
		tok = get_cmd_end(tok);
	}
	*tokens = tok;
	return (node);
}

t_anode			*create_node(t_token *ope, t_cmd *cmd)
{
	t_anode	*node;

	if (!(node = (t_anode *)malloc(sizeof(t_anode))))
		exit(-1);
	node->ope = ope;
	node->cmd = cmd;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return (node);
}

t_token			*create_ope_node(t_anode **tree, t_token *tokens)
{
	t_anode	*new;

	if (!(new = create_node(tokens, NULL)))
		return (NULL);
	new->left = *tree;
	if (tokens->type == TOKEN_PIPE)
	{
		tokens = tokens->next;
		new->right = ast_create_node(NULL, create_cmd(tokens));
		tokens = get_cmd_end(tokens);
	}
	else
	{
		tokens = tokens->next;
		new->right = create_cond_node(&tokens);
	}
	new->right->parent = new;
	(*tree)->parent = new;
	*tree = new;
	return (tokens);
}

t_token			*create_cmd_node(t_anode **tree, t_token *tokens)
{
	t_anode	*new;

	if (!(new = create_node(NULL, create_cmd(tokens))))
		return (NULL);
	if (*tree)
	{
		new->left = *tree;
		(*tree)->parent = new;
	}
	*tree = new;
	return (get_cmd_end(tokens));
}
