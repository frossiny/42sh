/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_resolve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:00:31 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/30 17:14:03 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "alias.h"
#include "lexer.h"

static int	alias_init(t_token *token, t_alias *alias, int *res, t_string **lst)
{
	if (!alias || !token)
		return (0);
	*res = 0;
	*lst = NULL;
	return (1);
}

static void	alias_empty_tok(t_shell *shell, t_token **token)
{
	t_token		*tok_lst;

	if (shell->lexer.tokens == *token)
	{
		shell->lexer.tokens = shell->lexer.tokens->next;
		tok_free(*token);
		*token = shell->lexer.tokens;
	}
	else
	{
		tok_lst = shell->lexer.tokens;
		while (tok_lst->next && tok_lst->next != *token)
			tok_lst = tok_lst->next;
		if (tok_lst)
		{
			tok_lst->next = (*token)->next;
			tok_free(*token);
			*token = tok_lst->next;
		}
		else
			*token = (*token)->next;
	}
}

char		*alias_solver(t_alias *alias, t_alias *curr, t_string **list,
																t_string *hist)
{
	t_alias		*tmp;

	if (!alias || !curr)
		return (NULL);
	if (curr->loop > 0)
		return (curr->key);
	curr->loop++;
	add_alias_history(list, curr->key);
	if (!is_already_solve(hist, curr->value)
			&& (tmp = alias_get(alias, curr->value)))
		return (alias_solver(alias, tmp, list, hist));
	return (curr->value);
}

int			alias_resolve(t_shell *shell, t_token *token, t_alias *alias
															, t_string **hist)
{
	int			res;
	char		*str;
	t_string	*list;

	if (!alias_init(token, alias, &res, &list))
		return (0);
	while (token)
		if (tok_is_word(token))
		{
			set_loop(alias);
			if (!is_already_solve(*hist, token->content)
				&& ((str = alias_solver(alias, alias_get(alias, token->content),
													&list, *hist))) && (++res))
				token->content = ft_strfdup(str, token->content);
			if (ft_strcmp(token->content, ""))
				while (token && (tok_is_word(token)
								|| tok_is_redirection(token)))
					token = token->next;
			else
				alias_empty_tok(shell, &token);
		}
		else
			token = token->next;
	maj_alias_history(list, hist);
	return (res);
}
