/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:23:37 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/29 17:22:43 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"
#include "ast.h"
#include "expansion.h"
#include "jobcontrol.h"
#include "execution.h"

static char		**split_var(char *var)
{
	char	**ret;
	size_t	i;

	if (!var)
		return (NULL);
	if (!(ret = ft_2dstrnew(2)))
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	ret[0] = ft_strndup(var, i);
	if (!var[i])
		return (ret);
	ret[1] = ft_strsub(var, i + 1, ft_strlen(var) - i);
	return (ret);
}

static void		parse_assignements(t_cmd *cmd, t_token **exe)
{
	t_token	*tok;
	char	**tmp;

	cmd->tenv = NULL;
	tmp = NULL;
	while (*exe && (*exe)->type == TOKEN_ASSIGNMENT)
	{
		tok = NULL;
		if (!(tmp = split_var((*exe)->content)))
			break ;
		if (tmp[1])
		{
			if (!(tok = tok_new(TOKEN_NAME, tmp[1])))
				break ;
			if (!expand(tok, 0, NULL))
				break ;
		}
		var_set(&(cmd->tenv), tmp[0], tmp[1] ? tok->content : NULL, 1);
		tok_free(tok);
		ft_strddel(&tmp);
		(*exe) = (*exe)->next;
	}
	if (tmp)
		ft_strddel(&tmp);
}

/*
**	Skip redirections tokens
*/

static t_token	*get_exe_token(t_token *exe)
{
	t_token		*prev;

	prev = NULL;
	while (tok_is_cmd_comp(exe))
	{
		if (prev && tok_is_redirection(prev))
		{
			prev = exe;
			exe = exe->next;
			continue ;
		}
		if (exe && exe->type == TOKEN_NAME)
			return (exe);
		prev = exe;
		exe = exe->next;
	}
	return (exe && exe->type == TOKEN_NAME ? exe : NULL);
}

static void		check_fg(t_token **exe)
{
	t_token		*new;
	t_token		*curr;
	t_token		*tmp;

	if (!exe || !*exe || (*exe)->content[0] != '%')
		return ;
	if (!(new = tok_new(TOKEN_NAME, "fg")))
		return ;
	new->next = *exe;
	curr = g_shell.lexer.tokens;
	tmp = NULL;
	while (curr)
	{
		if (curr == *exe)
		{
			if (tmp)
				tmp->next = new;
			else
				g_shell.lexer.tokens = new;
			break ;
		}
		tmp = curr;
		curr = curr->next;
	}
	*exe = new;
}

t_cmd			*create_cmd(t_token *exe)
{
	t_cmd	*cmd;
	char	*file;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	parse_assignements(cmd, &exe);
	check_fg(&exe);
	cmd->tokens = exe;
	cmd->exe = get_exe_token(exe);
	cmd->argc = -1;
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->allow_builtins = 1;
	cmd->is_bg = ast_is_bg(exe);
	if (cmd->exe)
	{
		file = exec_get_file(cmd, NULL, 0);
		cmd->exe_found = file != NULL;
		free(file);
	}
	cmd->redir = parse_redirections(exe);
	return (cmd);
}
