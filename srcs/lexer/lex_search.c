/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:02:36 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/15 14:49:54 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "tokens_list.h"

t_ex_token	lexer_search(const char *s)
{
	const t_ex_token	empty = {NULL, 0, TOKEN_NULL, ST_GENERAL};
	size_t				i;

	if (!s)
		return (empty);
	i = 0;
	while (g_tokens_list + i && (g_tokens_list[i]).op)
	{
		if (ft_strncmp(g_tokens_list[i].op, s, g_tokens_list[i].len) == 0)
			return (g_tokens_list[i]);
		i++;
	}
	return (empty);
}
