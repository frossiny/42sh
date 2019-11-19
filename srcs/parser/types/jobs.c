/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:49:24 by lubenard          #+#    #+#             */
/*   Updated: 2019/11/19 14:37:26 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "shell.h"
#include "jobcontrol.h"
# include <stdio.h>

int		par_type_jobs(t_parser *par)
{
	(void)par;
	printf("Je suis appele %s\n", par->tokens->content);
	new_jobs(g_shell.ast);
	par_next(par, 1);
	return (1);
}