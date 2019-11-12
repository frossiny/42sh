/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:26:37 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/06 18:17:58 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "shell.h"
#include "ast.h"
#include "utils.h"
#include "hashtable.h"
#include "builtins.h"

static int	start_process(char *file, t_cmd *cmd, char **env, t_shell *shell)
{
	int		status;

	if (!get_here_doc(cmd->redir, shell))
		return (EXIT_FAILURE);
	if ((g_child = fork()) == 0)
	{
		unregister_signals();
		shell->able_termcaps ? restore_shell(shell->prev_term) : 0;
		handle_redirections(cmd->redir);
		if (execve(file, cmd->args, env) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	close_here_docs(cmd->redir);
	if (g_child == -1)
		return (g_child = 0);
	waitpid(g_child, &status, 0);
	shell->able_termcaps ? termcaps_init(NULL) : 0;
	g_child = 0;
	if (WIFSIGNALED(status))
		return (display_signal(status));
	return (WEXITSTATUS(status));
}

static int	start(t_cmd *cmd, char **env, t_shell *shell)
{
	int		ret;
	char	*file;

	if (!cmd->allow_builtins || (ret = handle_builtin(cmd, shell)) == -1)
	{
		if (!(file = get_exe(shell, cmd->exe->content, 1)))
			return (127);
		if ((ret = can_execute(cmd->exe->content, shell)))
		{
			free(file);
			return (ret);
		}
		ret = start_process(file, cmd, env, shell);
		free(file);
	}
	return (ret);
}

int			execute(t_cmd *cmd, t_shell *shell)
{
	int		ret;
	char	**env;

	if (!cmd)
		return (1);
	if (build_args(cmd, shell->vars) < 1)
		return (1);
	cmd->redir = parse_redirections(cmd->exe);
	if (!validate_redirection(cmd->redir))
		return (1);
	env = var_build_env(shell->vars);
	ret = start(cmd, env, shell);
	ft_strddel(&env);
	return (ret);
}
