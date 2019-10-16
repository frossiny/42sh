/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:05:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/16 14:19:18 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "shell.h"
#include "lexer.h"
#include "ast.h"
#include "hashtable.h"

int		bslash_error(t_shell *shell, char **input, int ret)
{
	char	*ninput;
	char	*tmp;

	g_ignore_signals = 3;
	if (!(ret = get_input(0, &ninput, shell)))
	{
		if (g_ignore_signals)
		{
			write(1, "\n", 1);
			g_ignore_signals = 0;
			return (2);
		}
		return (130);
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

int		quote_error(t_shell *shell, char **input, int ret)
{
	char	*ninput;
	char	*tmp;

	g_ignore_signals = ret == -3 ? 2 : 1;
	if (!(ret = get_input(0, &ninput, shell)))
	{
		if (g_ignore_signals)
		{
			write(2,
			"42sh: unexpected EOF while looking for quote\n", 45);
			g_ignore_signals = 0;
			return (2);
		}
		return (130);
	}
	tmp = ft_strjoint(*input, "\n", ninput);
	free(*input);
	free(ninput);
	*input = tmp;
	g_ignore_signals = 0;
	return (0);
}

int		handle_input(t_shell *shell, char **input)
{
	int		ret;

	ret = 0;
	shell->lexer.size = 0;
	while ((ret = lex(*input, &(shell->lexer))) < 1)
	{
		destroy_lexer(&(shell->lexer));
		if (ret == -3 || ret == -2)
		{
			if ((ret = quote_error(shell, input, ret)))
				return (ret);
		}
		else if (ret == -4)
		{
			if ((ret = bslash_error(shell, input, ret)))
				return (ret);
		}
		else
			return (ret);
	}

/*
	t_token *tokens = g_shell.lexer.tokens;
	ft_printf("Tokens:\n");
	while (tokens)
	{
		ft_printf("%s\n", tokens->content);
		tokens = tokens->next;
	}*/
	
	return (0);
}

static int	eval_exec(char **input)
{
	int		ret;

	if (ft_strcmp(*input, "") == 0)
	{
		ft_strdel(input);
		return (g_return);
	}
	if ((ret = handle_input(&g_shell, input)) == 0)
	{
		if (!input)
			return (1);
		ft_strdel(input);
		build_ast(&g_shell);
		g_shell.ast ? ret = parse(&g_shell, g_shell.ast) : 0;
		destroy_lexer(&(g_shell.lexer));
		destroy_ast(&g_shell);
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
			g_return = eval_exec(&input);
	}
	if (input)
		ft_strdel(&input);
	isatty(0) ? ft_putchar('\n') : 0;
	var_destroy(&(g_shell.vars));
	ht_delete(g_shell);
	free_termcaps(&g_shell);
	return (g_return);
}
