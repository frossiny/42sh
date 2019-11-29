/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 10:41:29 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/26 10:44:51 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token		*tok_new(t_token_type type, char *content)
{
	t_token		*new;

	if (!(new = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	if (!(new->content = ft_strdup(content)))
	{
		free(new);
		return (NULL);
	}
	new->len = content ? ft_strlen(content) : 0;
	new->type = type;
	new->next = NULL;
	return (new);
}
