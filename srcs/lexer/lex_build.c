/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:39:03 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/07 16:15:28 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"
#include "shell.h"
#include "structs.h"
#include "lexer.h"
#include "history.h"

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
			return (2);
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
			return (1);
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

int				lex_build(t_shell *shell, char **input)
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
	return (ret);
}

int				lex_loop(t_shell *shell, char **input, int history)
{
	int			ret;

	ret = 0;
	if (isatty(0) && (ret = histo_expansion(shell, input)))
		return (0);
	if ((ret = lex_build(shell, input)) != 1)
		return (ret);
	if (isatty(0))
		history ? add_to_history(*input, &(shell->history)) : 0;
	if ((ret = alias_exec(shell, input)))
		return (ret);
	return (1);
}
