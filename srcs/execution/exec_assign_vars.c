/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_assign_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:04:58 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/28 11:25:18 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "variables.h"
#include "ast.h"

int		exec_assign_vars(t_cmd *cmd)
{
	t_var	*cur;

	cur = cmd->tenv;
	while (cur)
	{
		var_set(&(g_shell.vars), cur->key, cur->value, 0);
		cur = cur->next;
	}
	var_destroy(&(cmd->tenv));
	return (0);
}
