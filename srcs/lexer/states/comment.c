/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:22:01 by frossiny          #+#    #+#             */
/*   Updated: 2019/07/29 15:22:56 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		lex_state_comment(t_lexer *lexer)
{
	if (*(lexer->in) == '\n'
					&& !is_escaped(lexer->pin, lexer->in - lexer->pin, 0))
	{
		update_state(lexer, ST_GENERAL);
		lexer->pin = lexer->in;
	}
	else
		lexer->in++;
	return (1);
}
