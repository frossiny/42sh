/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_exp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:23:05 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/08 14:35:34 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "tokens_list.h"

t_exp_tok	*lex_new_exp(t_lexer *lexer, const char *op)
{
	t_exp_tok	*new;

	if (!(new = (t_exp_tok *)malloc(sizeof(t_exp_tok))))
		return (NULL);
	new->op = (char *)op;
	new->next = lexer->exps;
	lexer->exps = new;
	return (new);
}

void		lex_exp_del(t_lexer *lexer)
{
	t_exp_tok	*tmp;

	tmp = lexer->exps->next;
	free(lexer->exps);
	lexer->exps = tmp;
}
