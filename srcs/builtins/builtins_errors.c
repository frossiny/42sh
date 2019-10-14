/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 16:35:05 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/15 14:56:28 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "shell.h"

int		cd_exists(char *file, char *name)
{
	if (access(file, F_OK) == -1)
	{
		write(2, "cd: no such file or directory: ", 31);
		write(2, name, ft_strlen(name));
		ft_putchar_fd('\n', 2);
		return (0);
	}
	return (1);
}

void	env_invalid_arg(int *argc, char ***argv)
{
	write(2, "env: Invalid argument: ", 23);
	write(2, **argv, ft_strlen(**argv));
	(*argv)++;
	(*argc)--;
	ft_putchar_fd('\n', 2);
}
