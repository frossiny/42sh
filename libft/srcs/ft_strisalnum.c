/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisalnum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 12:18:29 by frossiny          #+#    #+#             */
/*   Updated: 2019/03/01 12:19:42 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strisalnum(char *str)
{
	while (*str)
	{
		if (!ft_isalnum(*str))
			return (0);
		str++;
	}
	return (1);
}
