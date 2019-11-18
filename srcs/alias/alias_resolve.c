/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_resolve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:00:31 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/15 17:23:13 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "alias.h"

void		alias_build_input(char **dest, t_token *token)
{
	char	*str;
	char	*tmp;

	if (!token)
		return ;
	str = NULL;
	while (token)
	{
		if (!str)
			str = ft_strdup(token->content);
		else
		{
			tmp = str;
			str = ft_strjoint(str, " ", token->content);
			free(tmp);
		}
		token = token->next;
	}
	free(*dest);
	*dest = str;
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

int			alias_resolve(t_token *token, t_alias *alias, t_string **hist)
{
	int			res;
	char		*str;
	t_string	*list;

	if (!alias || !token)
		return (0);
	res = 0;
	list = NULL;
	while (token)
	{
		if (token->type == TOKEN_NAME)
		{
			set_loop(alias);
			if (!is_already_solve(*hist, token->content)
				&& ((str = alias_solver(alias,
				alias_get(alias, token->content), &list, *hist))) && (++res))
				token->content = ft_strfdup(str, token->content);
			while (token && token->type == TOKEN_NAME)
				token = token->next;
		}
		else
			token = token->next;
	}
	maj_alias_history(list, hist);
	return (res);
}
