/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:35:05 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/23 14:55:03 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "shell.h"

int		cd_exists(char *file, char *name)
{
	if (access(file, F_OK) == -1)
	{
		ft_dprintf(2, "42sh: cd: no such file or directory: %s\n", name);
		return (0);
	}
	return (1);
}
