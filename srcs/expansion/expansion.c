/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:32:30 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/21 17:33:40 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "lexer.h"
#include "expansion.h"
#include "arithmetic.h"

static t_token		*del_empty_tokens(t_token *token, t_cmd *cmd)
{
	t_token	*prev;
	t_token	*curr;
	t_token	*next;

	exp_tok_clean(token);
	if (cmd->exe == token)
		cmd->exe = token->next;
	else if (cmd->exe->next)
	{
		prev = NULL;
		curr = cmd->exe->next;
		while (curr)
		{
			next = curr->next;
			if (curr == token)
				prev->next = token->next;
			curr = next;
		}
	}
	next = token->next;
	tok_free(token);
	return (next);
}

int				expand(t_token *tokens, int do_globbing, t_cmd *cmd)
{
	t_expansion		exp;
	t_token			*next;
	size_t			i;
	int				t;

	i = 0;
	while (tokens && (tok_is_word(tokens) || tok_is_redirection(tokens) \
		|| tokens->type == TOKEN_ASSIGNMENT))
	{
		next = tokens->next;
		t = 0;
		if (!(exp_variables(tokens)))
			return (0);
		if (cmd && ft_strequ("", tokens->content))
			if (!(tokens = del_empty_tokens(tokens, cmd)))
			{
				tokens = next;
				continue ;
			}
		if (tokens->content[0] == '~')
			if (!(handle_home(tokens, g_shell.vars)))
				return (0);
		if (!(replace_ae_token(tokens)))
			return (0);
		if (do_globbing)
			t = replace_globbing(tokens);
		exp_set_struct(&exp, tokens->content);
		if (!t && !exp_remove_quotes(&exp))
			return (0);
		if (exp.new)
			tok_replace(tokens, exp.new);
		tokens = next;
	}
	return (1);
}
