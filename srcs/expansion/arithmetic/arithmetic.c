/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:40:41 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/07 14:58:28 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arithmetic.h"

void	replace_ae_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
		if (tmp->type == TOKEN_ARITHMETIC && ft_strstr(token->content, "$(("))
		{
			//token->content = replace_ae(tmp->content);
			tmp->len = ft_strlen(tmp->content);
		}
}
