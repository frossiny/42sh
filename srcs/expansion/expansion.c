/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:32:30 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/25 10:31:53 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "lexer.h"
#include "expansion.h"
#include "arithmetic.h"

static	int		can_expand(t_token *token)
{
	return (token && (tok_is_word(token) || tok_is_redirection(token)
				|| token->type == TOKEN_ASSIGNMENT));
}

int				expand(t_token *tokens, int do_globbing, t_cmd *cmd)
{
	t_token		*next;
	size_t		i;
	int			t;

	i = 0;
	while (can_expand(tokens))
	{
		next = tokens->next;
		if (!(exp_variables(tokens)))
			return (0);
		if (cmd && ft_strequ("", tokens->content) \
				&& !(tokens = exp_del_empty_tokens(tokens, cmd)))
			break ;
		if (tokens->content[0] == '~' && !(handle_home(tokens, g_shell.vars)))
			return (0);
		if (!(replace_ae_token(tokens)))
			return (0);
		t = do_globbing ? replace_globbing(tokens) : 0;
		if (!t && !exp_remove_quotes(tokens))
			return (0);
		tokens = next;
	}
	return (1);
}
