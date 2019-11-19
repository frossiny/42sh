/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:34:54 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/18 16:07:03 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_LIST_H
# define TOKENS_LIST_H

static const t_ex_token	g_tokens_list[] =
{
	{"<<", 2, TOKEN_REDIRI, ST_OPERATOR},
	{">>", 2, TOKEN_REDIRO, ST_OPERATOR},
	{"&&", 2, TOKEN_AND, ST_OPERATOR},
	{"||", 2, TOKEN_OR, ST_OPERATOR},
	{"<&", 2, TOKEN_AGGR, ST_OPERATOR},
	{">&", 2, TOKEN_AGGR, ST_OPERATOR},
	{"|", 1, TOKEN_PIPE, ST_OPERATOR},
	{"<", 1, TOKEN_REDIRI, ST_OPERATOR},
	{">", 1, TOKEN_REDIRO, ST_OPERATOR},
	{";", 1, TOKEN_SEMI, ST_OPERATOR},
	{" ", 1, TOKEN_IGN, ST_OPERATOR},
	{"&", 1, TOKEN_JOBS, ST_OPERATOR},
	{"\n", 1, TOKEN_IGN, ST_OPERATOR},
	{"\v", 1, TOKEN_IGN, ST_OPERATOR},
	{"\t", 1, TOKEN_IGN, ST_OPERATOR},
	{"\r", 1, TOKEN_IGN, ST_OPERATOR},
	{"\f", 1, TOKEN_IGN, ST_OPERATOR},
	{NULL, 1, TOKEN_NULL, ST_OPERATOR}
};

static const t_ex_token	g_exp_list[] =
{
	{"$((", 3, TOKEN_ARITHMETIC, ST_OPERATOR},
	{"${", 2, TOKEN_VAR, ST_OPERATOR},
	//{"$", 1, TOKEN_VAR, ST_OPERATOR},
	{NULL, 1, TOKEN_NULL, ST_OPERATOR}
};

#endif
