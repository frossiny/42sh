/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 12:36:23 by frossiny          #+#    #+#             */
/*   Updated: 2019/08/13 12:36:45 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*get_file_start(char *word)
{
	char	*search;

	if (!(search = ft_strrchr(word, '/')))
		return (word[0] == '~' ? word + 1 : word);
	return (search + 1);
}
