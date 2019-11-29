/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_free_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:55:38 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/29 11:36:16 by frossiny         ###   ########.fr       */
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

void	u_free_shell(void)
{
	jobs_destroy_all(&g_shell);
	ast_destroy(&g_shell);
	var_destroy(&(g_shell.vars));
	alias_free_all(&(g_shell.alias));
	ht_delete(g_shell);
	lexer_free(&(g_shell.lexer));
	if (g_shell.history.lst)
		free_history(&(g_shell.history));
	g_pwd ? free(g_pwd) : 0;
}
