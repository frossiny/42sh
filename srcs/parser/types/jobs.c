/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:49:24 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/20 15:01:41 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shell.h"
#include "lexer.h"
#include "jobcontrol.h"

int			par_type_jobs(t_parser *par)
{
	if (!par->i)
		return (0);
	if (par->tokens->next && !tok_is_word(par->tokens->next))
	{
		par_next(par, 1);
		return (0);
	}
	par_next(par, 1);
	return (1);
}
