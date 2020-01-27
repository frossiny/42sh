/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:05:59 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/27 14:34:58 by frossiny         ###   ########.fr       */
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

extern char	**g_fc_tab;

int		handle_input(t_shell *shell, char **input, int history)
{
	int		ret;

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

	if (!*input || ft_strcmp(*input, "") == 0)
	{
		*input ? ft_strdel(input) : 0;
		return (g_return);
	}
	if ((ret = handle_input(&g_shell, input, history)) == 0)
	{
		if (!input)
			return (1);
		job_check_status();
		ft_strdel(input);
		ast_build(&g_shell);
		build_heredoc(&g_shell);
		ret = g_shell.ast ? exec_all(&g_shell, g_shell.ast) : 1;
		lexer_free(&(g_shell.lexer));
		ast_destroy(&g_shell);
	}
	else
		ft_strdel(input);
	return (ret);
}

int		check_exit(void)
{
	if (!g_shell.stopped_jobs && !job_can_exit())
	{
		g_shell.stopped_jobs = 1;
		ft_dprintf(2, "There are stopped jobs.\n");
		return (shell());
	}
	isatty(0) ? ft_putchar('\n') : 0;
	u_free_shell(1);
	return (0);
}

int		shell(void)
{
	char	*input;
	int		i;

	while ((get_input(0, &input, &g_shell)) > 0)
	{
		if (!input && g_return != 130)
			g_return = 1;
		else
			g_return = eval_exec(&input, 1);
		i = 0;
		while (g_fc_tab && g_fc_tab[i])
		{
			ft_putendl(g_fc_tab[i]);
			g_return = eval_exec(&g_fc_tab[i++], 1);
		}
		ft_2dstrdel(&g_fc_tab);
	}
	if (input)
		ft_strdel(&input);
	check_exit();
	return (g_return);
}
