/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:14:27 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/09 16:13:27 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "reader.h"
#include "lexer.h"
#include "expansion.h"

static int	build_args_arr(char ***args, t_token *tokens)
{
	int		argc;
	int		i;
	t_token	*tmp;

	argc = 0;
	tmp = tokens;
	while (tmp && (tok_is_word(tmp) || tok_is_redirection(tmp)))
	{
		argc += tok_is_word(tmp);
		tmp = tmp->next;
	}
	if (!((*args) = (char **)malloc(sizeof(char *) * (argc + 1))))
		exit(-1);
	tmp = tokens;
	i = 0;
	while (tmp && i < argc)
	{
		if (tok_is_word(tmp))
			(*args)[i++] = tmp->content;
		tmp = tmp->next;
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
	if (!expand(cmd->exe))
		return (-1);
	cmd->argc = build_args_arr(&argv, cmd->exe);
	cmd->args = argv;
	return (cmd->argc);
}
