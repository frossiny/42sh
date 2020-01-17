/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_specials.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:31:36 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/17 19:11:16 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "execution.h"

int		exe_specials(t_cmd *cmd)
{
	int		ret;

	ret = 0;
	if (!cmd)
		return (1);
	if (cmd->tenv)
		ret = exec_assign_vars(cmd);
	if (cmd->redir)
		handle_redirections(cmd->redir, 1);
	return (ret);
}
