/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_resolve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:00:31 by vsaltel           #+#    #+#             */
/*   Updated: 2020/02/19 14:35:16 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "alias.h"
#include "lexer.h"

void			alias_patch_token_list(t_token *dest, t_token *new)
{
	t_token *tmp;

	if (!new)
		return ;
	dest->content = ft_strfdup(new->content, dest->content);
	tmp = new;
	new = new->next;
	tok_free(tmp);
	if (new)
	{
		tmp = dest->next;
		dest->next = new;
		while (new && new->next)
			new = new->next;
		new->next = tmp;
	}
}

int				alias_resolve(t_alias *alias, t_token *token, t_string *hist)
{
	t_alias		*res;
	t_lexer		lexer;
	char		*tmp;
	int			ret;

	ret = 1;
	if ((res = alias_get(alias, token->content)))
	{
		if (res && res->value[0])
		{
			tmp = ft_strdup(res->value);
			if ((ret = alias_lex(&lexer, &tmp)) != 1)
				return (ret);
			if (alias_recursive(alias, lexer.tokens, hist, token->content))
				return (1);
			alias_patch_token_list(token, lexer.tokens);
		}
		else if (res && !res->value[0])
			token->content = ft_strfdup("", token->content);
	}
	return (0);
}

void			move_token_index(t_token **tok)
{
	t_token		*token;

	token = *tok;
	while (token && (tok_is_word(token) || tok_is_redirection(token)))
		token = token->next;
	if (token)
		token = token->next;
	*tok = token;
}

int				alias_recursive(t_alias *alias, t_token *token,
											t_string *hist, char *old_word)
{
	t_string	*new_hist;
	t_token		*tmp;
	t_token		*deb;
	int			ret;

	new_hist = t_stringdup(hist);
	new_hist = old_word ? add_alias_history(new_hist, old_word) : new_hist;
	deb = token;
	while (token)
	{
		tmp = NULL;
		if (tok_is_word(token) && !is_already_solve(new_hist, token->content))
		{
			tmp = token->next;
			if ((ret = alias_resolve(alias, token, new_hist)))
			{
				free_alias_history(&new_hist);
				return (ret);
			}
			token = tmp;
		}
		move_token_index(&token);
	}
	free_alias_history(&new_hist);
	return (0);
}
