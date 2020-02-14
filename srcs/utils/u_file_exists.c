/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_file_exists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:24:12 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/14 16:19:21 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		u_file_exists(char *path, int verbose)
{
	if (!path)
	{
		if (verbose)
			inexistant(NULL);
		return (0);
	}
	if (access(path, F_OK))
	{
		if (verbose)
			inexistant(path);
		return (0);
	}
	return (1);
}
