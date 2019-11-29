/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:26:37 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/29 16:44:15 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ast.h"
#include "execution.h"
#include "utils.h"
#include "builtins.h"
#include "jobcontrol.h"

static int	start_process(char *file, t_cmd *cmd, char **env)
{
	int		status;
	int		wpid;

	if (!get_here_doc(cmd->redir, &g_shell))
		return (EXIT_FAILURE);
	if ((g_child = fork()) > 0 && cmd->is_bg)
		job_new(cmd, g_child);
	if (!g_child)
	{
		if (!cmd->is_bg && g_shell.able_termcaps)
			restore_shell(g_shell.prev_term);
		unregister_signals();
		cmd->is_bg ? setpgid(0, 0) : 0;
		handle_redirections(cmd->redir, 0);
		if (execve(file, cmd->args, env) == -1)
			exit(EXIT_FAILURE);
	}
	close_here_docs(cmd->redir);
	g_shell.current_cmd = cmd;
	if (g_child == -1)
		return (g_child = 0);
	wpid = 0;
	while (g_child && !wpid && !cmd->is_bg)
	{
		pause();
		wpid = waitpid(g_child, &status, WNOHANG);
	}
	!cmd->is_bg && g_shell.able_termcaps ? termcaps_init(NULL) : 0;
	g_child = 0;
	g_shell.current_cmd = NULL;
	if (WIFSIGNALED(status))
		return (display_signal(status));
	return (WEXITSTATUS(status));
}

static int	start(t_cmd *cmd, char **env)
{
	int		ret;
	char	*file;

	if (!cmd->allow_builtins || (ret = handle_builtin(cmd, &g_shell)) == -1)
	{
		if (!(file = get_exe(&g_shell, cmd->exe->content, 1)))
			return (127);
		if ((ret = can_execute(cmd->exe->content, &g_shell)))
		{
			free(file);
			return (ret);
		}
		ret = start_process(file, cmd, env);
		free(file);
	}
	return (ret);
}

int			exec_command(t_cmd *cmd)
{
	int		ret;
	char	**env;

	if (!cmd)
		return (1);
	if (ast_build_args(cmd, g_shell.vars) < 0)
		return (1);
	cmd->redir = parse_redirections(cmd->tokens);
	if (!validate_redirection(cmd->redir))
		return (1);
	if (!cmd->exe)
		return (exe_specials(cmd));
	var_merge(&(cmd->tenv), g_shell.vars);
	env = !is_builtin(cmd->exe->content) ? var_build_env(cmd->tenv) : NULL;
	ret = start(cmd, env);
	var_destroy(&(cmd->tenv));
	ft_2dstrdel(env);
	return (ret);
}
