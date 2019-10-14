/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:54:11 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/28 15:38:53 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**dup_argv(int argc, char **args, char ***argv)
{
	char	**new;
	int		i;

	if (!(new = (char **)malloc(sizeof(char *) * (argc + 1))))
		exit(1);
	i = -1;
	while (++i < argc)
		new[i] = args[i];
	new[i] = NULL;
	free(*argv);
	*argv = new;
	return (new);
}
