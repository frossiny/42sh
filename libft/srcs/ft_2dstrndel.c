/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dstrndel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:05:39 by pcharrie          #+#    #+#             */
/*   Updated: 2019/11/01 16:06:32 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_2dstrndel(char ***tab, int size)
{
	if (!tab)
		return ;
	while (size >= 0)
		ft_strdel(&(*tab)[size--]);
	free(*tab);
	*tab = NULL;
}
