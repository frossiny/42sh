/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:14:27 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/26 12:49:38 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "reader.h"
#include "lexer.h"
#include "expansion.h"

static int	is_arg(t_token *token)
{
	if (!token)
		return (0);
	return (tok_is_word(token) || tok_is_redirection(token));
}

static int	count_args(t_token *tokens)
{
	t_token	*prev;
	int		argc;

	argc = 0;
	prev = NULL;
	while (is_arg(tokens))
	{
		if (tok_is_word(tokens) && !tok_is_redirection(prev))
			argc++;
		prev = tokens;
		tokens = tokens->next;
	}
	return (argc);
}

static int	build_args_arr(char ***args, t_token *tokens)
{
	int		argc;
	int		i;
	t_token	*prev;

	argc = count_args(tokens);
	if (!((*args) = (char **)malloc(sizeof(char *) * (argc + 1))))
		exit(-1);
	prev = NULL;
	i = 0;
	while (is_arg(tokens) && i < argc)
	{
		if (tok_is_word(tokens) && !tok_is_redirection(prev))
			(*args)[i++] = tokens->content;
		tokens = tokens->next;
	}
	(*args)[i] = NULL;
	return (argc);
}

int			build_args(t_cmd *cmd)
{
	char	**argv;

	if (!cmd)
		return (-1);
	if (!cmd->exe && cmd->tenv)
		return (1);
	if (!expand(cmd->exe, 1, cmd))
		return (-1);
	cmd->argc = build_args_arr(&argv, cmd->exe);
	cmd->args = argv;
	return (cmd->argc);
}
