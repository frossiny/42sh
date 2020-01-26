/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_first.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:50:03 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/26 15:50:33 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*extract_first(char *command, char stop)
{
	int		i;

	i = 0;
	while (command[i] != stop && command[i])
		++i;
	return (ft_strsub(command, 0, i));
}
