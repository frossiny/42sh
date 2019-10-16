/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:54:50 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/16 14:18:46 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void	inexistant(char *name)
{
	write(2, "42sh: no such file or directory: ", 33);
	write(2, name, ft_strlen(name));
	ft_putchar_fd('\n', 2);
}

void	not_found(char *name)
{
	write(2, "42sh: command not found: ", 25);
	write(2, name, ft_strlen(name));
	ft_putchar_fd('\n', 2);
}

int		permission_denied(char *name)
{
	write(2, "42sh: permission denied: ", 25);
	write(2, name, ft_strlen(name));
	ft_putchar_fd('\n', 2);
	return (126);
}

void	no_user(char *name)
{
	write(2, "42sh: no such user or named directory: ", 39);
	write(2, name, ft_strlen(name));
	ft_putchar_fd('\n', 2);
}

int		is_directory_err(char *name)
{
	write(2, "42sh: ", 6);
	write(2, name, ft_strlen(name));
	write(2, ": is a directory\n", 17);
	return (126);
}
