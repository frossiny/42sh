/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:54:50 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/23 15:59:10 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void	inexistant(char *name)
{
	ft_dprintf(2, "42sh: %s: no such file or directory\n", name);
}

void	not_found(char *name)
{
	ft_dprintf(2, "42sh: %s: command not found\n", name);
}

int		permission_denied(char *name)
{
	ft_dprintf(2, "42sh: %s: permission denied\n", name);
	return (126);
}

void	no_user(char *name)
{
	ft_dprintf(2, "42sh: %s: no such user or named directory\n", name);
}

int		is_directory_err(char *name, int verbose)
{
	if (verbose)
		ft_dprintf(2, "42sh: %s: is a directory\n", name);
	return (126);
}
