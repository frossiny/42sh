/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:34:54 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/15 15:28:01 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_LIST_H
# define TOKENS_LIST_H

static const t_ex_token g_tokens_list[] =
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
	{";", 1, TOKEN_SEMI, ST_SEMIC},
	{" ", 1, TOKEN_IGN, ST_GENERAL},
	{"\n", 1, TOKEN_IGN, ST_GENERAL},
	{"\v", 1, TOKEN_IGN, ST_GENERAL},
	{"\t", 1, TOKEN_IGN, ST_GENERAL},
	{"\r", 1, TOKEN_IGN, ST_GENERAL},
	{"\f", 1, TOKEN_IGN, ST_GENERAL},
	{NULL, 1, TOKEN_NULL, ST_GENERAL}
};

#endif
