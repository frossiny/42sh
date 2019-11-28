/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:45:17 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/28 11:54:20 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtins.h"
#include "ast.h"

int		exec_pipe_builtin(t_pipel *pline, t_fd *fd, t_shell *shell)
{
	t_builtin	builtin;
	t_cmd		*cmd;
	int			ret;
	int			sfd[3];

	cmd = pline->cmd;
	if (!is_builtin(cmd->exe->content))
		return (exec_pipe_cmd(pline, fd, shell));
	if (!(ret = validate_redirection(cmd->redir)))
		return (!ret);
	if (!(builtin = get_builtin(cmd->exe->content)).func)
		return (-1);
	if (cmd->redir)
	{
		sfd[0] = dup(0);
		sfd[1] = fd->sfd;
		sfd[2] = dup(2);
	}
	if (pline->next)
		dup2(fd->np[1], 1);
	handle_redirections(cmd->redir, 0);
	ret = builtin.func(cmd, shell);
	cmd->redir ? restore_fd(sfd) : dup2(fd->sfd, 1);
	return (ret);
}
