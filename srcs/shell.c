/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:05:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/29 15:29:03 by vsaltel          ###   ########.fr       */
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
#include "jobcontrol.h"

int		handle_input(t_shell *shell, char **input, int history)
{
	int			ret;

	ret = 0;
	if ((ret = lex_loop(shell, input, history)) != 1)
		return (ret);
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
	if (!job_can_exit())
	{
		ft_printf("There are stopped jobs.\n");
		return (shell());
	}
	isatty(0) ? ft_putchar('\n') : 0;
	var_destroy(&(g_shell.vars));
	alias_free_all(&(g_shell.alias));
	ht_delete(g_shell);
	free_termcaps(&g_shell);
	free(g_pwd);
	return (g_return);
}
