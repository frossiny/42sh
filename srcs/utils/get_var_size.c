/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:53:45 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/08 11:06:32 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

size_t	get_var_size(char *key)
{
	size_t	ret;

	if (!key)
		return (0);
	ret = -1;
	if (ft_strchr(EXP_SPECIAL, key[0]))
		return (1);
	while (key[++ret])
	{
		if (!ft_isalnum(key[ret]) && key[ret] != '_')
			break ;
	}
	return (ret);
}
