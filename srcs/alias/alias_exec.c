/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:55:33 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/18 17:51:55 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"
#include "shell.h"
#include "structs.h"
#include "lexer.h"

static int		bslash_error(t_shell *shell, char **input, int ret)
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

static int		quote_error(t_shell *shell, char **input, int ret)
{
	char	*ninput;
	char	*tmp;

	g_ignore_signals = ret == -3 ? 2 : 1;
	if (!(ret = get_input(0, &ninput, shell)))
	{
		if (g_ignore_signals)
		{
			ft_dprintf(2, "42sh: unexpected EOF while looking for quote\n");
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

static int		lexing(t_shell *shell, char **input)
{
	int			ret;

	ret = 0;
	alias_build_input(input, shell->lexer.tokens);
	lexer_free(&(shell->lexer));
	shell->lexer.size = 0;
	while ((ret = lex(*input, &(shell->lexer))) < 1)
	{
		lexer_free(&(shell->lexer));
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
	return (ret);
}

int				alias_exec(t_shell *shell, char **input)
{
	int			ret;
	int			alias_ret;
	t_string	*alias_hist;

	ret = 0;
	alias_hist = NULL;
	alias_ret = alias_resolve(shell->lexer.tokens, shell->alias, &alias_hist);
	while (alias_ret > 0)
	{
		if ((ret = lexing(shell, input)))
			return (ret);
		alias_ret = alias_resolve(shell->lexer.tokens, shell->alias,
															&alias_hist);
	}
	free_alias_history(&alias_hist);
	return (0);
}
