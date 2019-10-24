/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:49:27 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/24 12:50:25 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

int		par_type_semic(t_parser *par)
{
	if (par->tokens->next && !tok_is_word(par->tokens->next))
	{
		par_next(par, 1);
		return (0);
	}
	par_next(par, 1);
	return (1);
}
