/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:49:24 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/21 17:59:34 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shell.h"
#include "lexer.h"
#include "jobcontrol.h"

int		par_type_jobs(t_parser *par)
{
	if (!par->i)
		return (0);
	/*if (!tok_is_word(par->tokens->next))
	{
		par_next(par, 1);
		return (0);
	}*/
	job_new(g_shell.ast);
	g_shell.jobs->is_jobs = 1;
	par_next(par, 1);
	return (1);
}
