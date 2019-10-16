/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:38:16 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/16 13:13:42 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_var	*var_init(char *envp[])
{
	char	**split;

	g_shell.vars = NULL;
	while (*envp)
	{
		split = ft_strsplit(*envp, '=');
		var_set(&(g_shell.vars), split[0], split[1], 1);
		ft_strddel(&split);
		envp++;
	}
	return (g_shell.vars);
}
