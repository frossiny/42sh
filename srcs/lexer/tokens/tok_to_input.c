/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_to_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:31:28 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/30 16:14:00 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

void			tok_to_input(char **dest, t_token *token)
{
	char	*str;
	char	*tmp;

	if (!token)
	{
		free(*dest);
		*dest = ft_strdup("");
		return ;
	}
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
