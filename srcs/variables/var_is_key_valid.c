/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_is_key_valid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 20:13:46 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/03 18:58:26 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		var_is_key_valid(char *str, size_t len)
{
	if (!str || ft_isdigit(str[0]))
		return (0);
	if (len == 0)
		len = ft_strlen(str);
	while (*str && len--)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}
