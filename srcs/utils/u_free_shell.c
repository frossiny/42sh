/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_free_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:55:38 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/13 17:28:05 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ast.h"
#include "jobcontrol.h"
#include "lexer.h"
#include "variables.h"
#include "alias.h"
#include "hashtable.h"
#include "termcaps.h"
#include "history.h"
#include "execution.h"

void	u_free_shell(int kill_jobs)
{
	jobs_destroy_all(&g_shell, kill_jobs);
	ast_free_cmd(g_shell.current_cmd);
	exec_del_pipeline(g_shell.current_pipel);
	ast_destroy(&g_shell);
	var_destroy(&(g_shell.vars));
	alias_free_all(&(g_shell.alias));
	ht_delete(g_shell);
	lexer_free(&(g_shell.lexer));
	if (g_shell.history.lst)
	{
		if (kill_jobs)
			overwrite_history(g_shell.history.lst);
		free_history(&(g_shell.history));
	}
	ft_strdel(&g_shell.ps1);
	restore_shell(g_shell.prev_term);
	g_pwd ? free(g_pwd) : 0;
}
