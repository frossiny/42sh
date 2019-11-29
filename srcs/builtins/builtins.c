/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:03:28 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/29 10:46:03 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execution.h"
#include "builtins.h"

int					is_builtin(char *name)
{
	size_t	i;

	i = 0;
	if (!name)
		return (0);
	while (g_builtins[i].name)
	{
		if (ft_strcmp(name, g_builtins[i].name) == 0)
			return (1);
		i++;
	}
	return (0);
}

t_builtin			get_builtin(char *name)
{
	const	t_builtin	nbuiltin = { NULL, NULL };
	size_t				i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strcmp(name, g_builtins[i].name) == 0
												&& g_builtins[i].func)
			return (g_builtins[i]);
		i++;
	}
	return (nbuiltin);
}

void				restore_fd(int fd[])
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	dup2(fd[2], 2);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
}

int					handle_builtin(t_cmd *cmd, t_shell *shell)
{
	t_builtin	builtin;
	int			ret;
	int			fd[3];

	if (!cmd->exe || !cmd->exe->content)
		return (-1);
	if (cmd->is_bg)
		return (exec_fork_builtin(cmd));
	if (!(builtin = get_builtin(cmd->exe->content)).func)
		return (-1);
	if (cmd->redir)
	{
		fd[0] = dup2(0, 50);
		fd[1] = dup2(1, 51);
		fd[2] = dup2(2, 52);
	}
	if (!handle_redirections(cmd->redir, 0))
		return (1);
	ret = builtin.func(cmd, shell);
	if (cmd->redir)
		restore_fd(fd);
	return (ret);
}
