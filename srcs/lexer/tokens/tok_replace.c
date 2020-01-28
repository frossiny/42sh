/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 17:30:43 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/28 12:00:58 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

void	tok_replace(t_token *token, char *str)
{
	ft_strdel(&token->content);
	if (!str)
		str = ft_strdup("");
	token->content = str;
	token->len = ft_strlen(str);
}
