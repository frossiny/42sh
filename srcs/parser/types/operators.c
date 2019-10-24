/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:08:57 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/24 12:48:45 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

int		par_type_operator(t_parser *par)
{
	if (!tok_is_word(par->tokens->next))
	{
		par_next(par, 1);
		return (0);
	}
	par_next(par, 1);
	return (1);
}
