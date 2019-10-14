/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:10:27 by vsaltel           #+#    #+#             */
/*   Updated: 2019/05/07 15:11:07 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinf(char const *s1, char const *s2)
{
	char	*dst;

	if (!s1 || !s2 || !(dst = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(dst, s1);
	ft_strcat(dst, s2);
	free((char *)s1);
	free((char *)s2);
	return (dst);
}
