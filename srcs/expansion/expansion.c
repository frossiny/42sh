/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:32:30 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/01 17:52:23 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "lexer.h"
#include "expansion.h"

static void		init_exp(t_expansion *exp, char *content)
{
	exp->i = -1;
	exp->li = 0;
	exp->isquote = 0;
	exp->str = content;
	exp->new = NULL;
}

int				expand(t_token *tokens)
{
	t_expansion		exp;

	while (tokens)
	{
		if (tokens->content[0] == '~')
			if (!(handle_home(tokens, g_shell.vars)))
				return (0);
		init_exp(&exp, tokens->content);
		if (!exp_remove_quotes(&exp))
			return (0);
		if (exp.new)
			tok_replace(tokens, exp.new);
		tokens = tokens->next;
	}
	return (1);
}
