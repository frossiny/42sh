/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:14:27 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/29 16:47:28 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "parser.h"
#include "lexer.h"

static int	build_args_arr(char ***args, t_token *tokens)
{
	int		argc;
	int		i;
	t_token	*tmp;

	argc = 0;
	tmp = tokens;
	while (tmp && is_word_token(tmp))
	{
		if (ft_strisdigit(tmp->content) && tmp->next
		&& tmp->next->type == TOKEN_REDIRI && tmp->next->type == TOKEN_REDIRO)
			break ;
		argc++;
		tmp = tmp->next;
	}
	if (!((*args) = (char **)malloc(sizeof(char *) * (argc + 1))))
		exit(-1);
	tmp = tokens;
	i = 0;
	while (tmp && i < argc)
	{
		(*args)[i++] = tmp->content;
		tmp = tmp->next;
	}
	(*args)[i] = NULL;
	return (argc);
}

int			build_args(t_cmd *cmd, t_var *vars)
{
	char	**argv;

	if (!cmd)
		return (-1);
	replace_globing(cmd->exe, vars);
	replace_vars(cmd->exe, vars);
	cmd->argc = build_args_arr(&argv, cmd->exe);
	cmd->args = argv;
	return (cmd->argc);
}
