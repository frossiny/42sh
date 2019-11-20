/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:32:30 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/20 15:15:19 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "lexer.h"
#include "expansion.h"
#include "arithmetic.h"

int				expand(t_token *tokens, int do_globbing)
{
	t_expansion		exp;
	t_token			*next;
	size_t			i;

	i = 0;
	while (tokens)
	{
		next = NULL;
		if (tokens->content[0] == '~')
			if (!(handle_home(tokens, g_shell.vars)))
				return (0);
		if (!(exp_variables(tokens)))
			return (0);
		if (!(replace_ae_token(tokens)))
			return (0);
		if (do_globbing)
			replace_globbing(tokens, &next);
		exp_set_struct(&exp, tokens->content);
		if (!exp_remove_quotes(&exp))
			return (0);
		if (exp.new)
			tok_replace(tokens, exp.new);
		tokens = do_globbing ? next : tokens->next;
	}
	return (1);
}
