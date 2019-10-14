/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:22:18 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/21 14:22:44 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strfdup(const char *s1, const char *f)
{
	char	*dest;

	if (!(dest = ft_strnew(ft_strlen(s1))))
		return (NULL);
	ft_strcpy(dest, s1);
	free((char *)f);
	return (dest);
}
