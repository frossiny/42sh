/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:46:30 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/27 19:03:13 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strnncmp(char *dest, char *src, int start, int end)
{
	int		i;

	i = 0;
	if (start < 0 || end < 0)
		return (0);
	while (dest[start] && src[i] && dest[start] == src[i] && start != end)
	{
		start++;
		i++;
	}
	return ((unsigned char)dest[start] - (unsigned char)src[i]);
}
