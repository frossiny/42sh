/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:05:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/28 11:36:47 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "alias.h"
#include "hashtable.h"
#include "execution.h"

static int		bslash_error(t_shell *shell, char **input, int ret)
{
	char	*ninput;
	char	*tmp;

	g_ignore_signals = 1;
	if (!(ret = get_input(0, &ninput, shell)))
	{
		if (g_ignore_signals)
		{
			g_ignore_signals = 0;
			return (1);
		}
		return (258);
	}
	if (ninput)
	{
		tmp = ft_strjoin(*input, (*ninput == '\\') ? ninput + 1 : ninput);
		free(*input);
		free(ninput);
		*input = tmp;
	}
	g_ignore_signals = 0;
	return (0);
}

static int		not_closed_error(t_shell *shell, char **input, int ret)
{
	char	*ninput;
	char	*tmp;

	g_ignore_signals = 1;
	if (!(ret = get_input(0, &ninput, shell)))
	{
		if (g_ignore_signals)
		{
			ft_dprintf(2, "42sh: unexpected EOF\n");
			g_ignore_signals = 0;
			return (2);
		}
		return (258);
	}
	tmp = ft_strjoint(*input, "\n", ninput);
	free(*input);
	free(ninput);
	*input = tmp;
	g_ignore_signals = 0;
	return (0);
}

int		handle_input(t_shell *shell, char **input, int history)
{
	int			ret;

	ret = 0;
	shell->lexer.size = 0;
	while ((ret = lex(*input, &(shell->lexer))) < 1)
	{
		lexer_free(&(shell->lexer));
		if (ret > -2)
			return (ret);
		else if (ret == -2 && (ret = not_closed_error(shell, input, ret)))
			return (ret);
		else if (ret == -3 && (ret = bslash_error(shell, input, ret)))
			return (ret);
	}
	history ? add_to_history(*input, &(shell->history)) : 0;
	alias_exec(shell, input);
	if (!parse(shell->lexer.tokens))
	{
		lexer_free(&(shell->lexer));
		return (1);
	}
	return (0);
}

int		eval_exec(char **input, int history)
{
	int		ret;

	if (ft_strcmp(*input, "") == 0)
	{
		ft_strdel(input);
		return (g_return);
	}
	if ((ret = handle_input(&g_shell, input, history)) == 0)
	{
		if (!input)
			return (1);
		ft_strdel(input);
		ast_build(&g_shell);
		g_shell.ast ? ret = exec_all(&g_shell, g_shell.ast) : 0;
		lexer_free(&(g_shell.lexer));
		ast_destroy(&g_shell);
	}
	else
		ft_strdel(input);
	return (ret);
}

int		shell(void)
{
	char	*input;

	while ((get_input(0, &input, &g_shell)) > 0)
	{
		if (!input)
			g_return = 1;
		else
			g_return = eval_exec(&input, 1);
	}
	if (input)
		ft_strdel(&input);
	isatty(0) ? ft_putchar('\n') : 0;
	var_destroy(&(g_shell.vars));
	alias_free_all(&(g_shell.alias));
	ht_delete(g_shell);
	free_termcaps(&g_shell);
	free(g_pwd);
	return (g_return);
}
