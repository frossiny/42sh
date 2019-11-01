/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_is_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:56:53 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/01 15:38:56 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "utils.h"
#include "tokens_list.h"

size_t	lex_get_expansion(t_lexer *lex)
{
	size_t	i;

	i = 0;
	while (g_exp_list + i && (g_exp_list[i]).op)
	{
		if (ft_strnequ(g_exp_list[i].op, lex->in, g_exp_list[i].len))
			if (!is_escaped(lex->pin, lex->in - lex->pin, 0))
				break ;
		i++;
	}
	return (i);
}

int		lex_is_expansion(t_lexer *lex)
{
	size_t	i;

	i = 0;
	while (g_exp_list + i && (g_exp_list[i]).op)
	{
		if (ft_strnequ(g_exp_list[i].op, lex->in, g_exp_list[i].len))
			if (!is_escaped(lex->pin, lex->in - lex->pin, 0))
				return (1);
		i++;
	}
	return (0);
}
