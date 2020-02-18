/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_file_can_read.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:24:12 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/14 16:17:26 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		u_file_can_read(char *path)
{
	if (!path)
	{
		inexistant(NULL);
		return (0);
	}
	if (access(path, R_OK))
	{
		permission_denied(path);
		return (0);
	}
	return (1);
}
