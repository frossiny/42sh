/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:59:32 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/20 15:00:44 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

int		par_type_conditions(t_parser *par)
{
	if (par->i == 0)
		return (0);
	if (!tok_is_word(par->tokens->next) && !tok_is_varexp(par->tokens->next))
	{
		par_next(par, 1);
		return (0);
	}
	par_next(par, 1);
	return (1);
}
