/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:53:45 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/15 14:59:22 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

size_t	get_var_size(char *key)
{
	size_t	ret;

	if (!key || key[0] != '$')
		return (0);
	key++;
	ret = -1;
	while (key[++ret])
	{
		if (key[ret] == '?')
			return (1);
		if (!ft_isalnum(key[ret]) && key[ret] != '_')
			break ;
	}
	return (ret);
}
