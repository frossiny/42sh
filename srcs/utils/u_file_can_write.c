/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_file_can_write.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:24:12 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/14 16:33:13 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <fcntl.h>

int		u_file_can_write(char *path)
{
	int		fd;

	if (!path)
	{
		inexistant(NULL);
		return (0);
	}
	if ((fd = open(path, O_WRONLY | O_CREAT, 420)) == -1)
	{
		permission_denied(path);
		return (0);
	}
	close(fd);
	return (1);
}
