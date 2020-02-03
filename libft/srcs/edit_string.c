/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 20:22:32 by alagroy-          #+#    #+#             */
/*   Updated: 2020/02/03 20:33:25 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_insert_str(char *s, char *insert, int index)
{
	char	*rtrn;

	if (index > (int)ft_strlen(s))
		return (NULL);
	if (!(rtrn = (char *)malloc(((ft_strlen(s) + ft_strlen(insert) + 1)
						* sizeof(char)))))
		return (NULL);
	ft_bzero(rtrn, ft_strlen(s) + ft_strlen(insert) + 1);
	rtrn[ft_strlen(s) + ft_strlen(insert)] = '\0';
	ft_strncpy(rtrn, s, index);
	ft_strcat(rtrn, insert);
	ft_strcat(rtrn, s + index);
	free(s);
	free(insert);
	return (rtrn);
}

char	*ft_strdelpart(char *s, int index, int nb_char)
{
	char	*rtrn;
	char	*sub;
	char	*sub2;

	sub = ft_strsub(s, 0, index);
	sub2 = ft_strsub(s, index + nb_char, ft_strlen(s) - index - nb_char);
	if (!(rtrn = ft_strjoin(sub, sub2)))
		return (NULL);
	free(s);
	free(sub);
	free(sub2);
	return (rtrn);
}
