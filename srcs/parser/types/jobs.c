/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:49:24 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/27 18:44:34 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shell.h"
#include "lexer.h"
#include "jobcontrol.h"

static int	validate(t_token *token)
{
	if (!token)
		return (1); 
	return (token->type == TOKEN_SEMI);
}

int			par_type_jobs(t_parser *par)
{
	if (!par->i)
		return (0);
	if (!validate(par->tokens->next))
	{
		par_next(par, 1);
		return (0);
	}
	job_new();
	par_next(par, 1);
	return (1);
}
