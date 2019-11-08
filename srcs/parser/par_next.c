/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:47:11 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/23 18:05:26 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	par_next(t_parser *parser, int i)
{
	if (!parser)
		return ;
	while (parser->tokens && i)
	{
		parser->tokens = parser->tokens->next;
		parser->i++;
		i--;
	}
}
