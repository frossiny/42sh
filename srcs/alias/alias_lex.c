/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:31:13 by vsaltel           #+#    #+#             */
/*   Updated: 2020/02/17 17:53:55 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"
#include "shell.h"
#include "structs.h"
#include "lexer.h"

int		alias_lex(t_lexer *lexer, char **input)
{
	int			ret;

	ret = 0;
	lexer->size = 0;
	lexer->exps = NULL;
	lexer->tokens = NULL;
	lexer->state = ST_GENERAL;
	lexer->lstate = ST_GENERAL;
	while ((ret = lex(*input, lexer)) < 1)
	{
		lexer_free(lexer);
		if (ret > -2)
			break ;
		else if (ret == -2 && (ret = not_closed_error(input, ret)))
			break ;
		else if (ret == -3 && (ret = bslash_error(input, ret)))
			break ;
	}
	free(*input);
	return (ret);
}
