/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tilde.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:14:30 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 18:27:56 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

char		*get_tilde(char *word, t_var *vars)
{
	char *tmp;
	char *path;
	char *search;

	path = NULL;
	if ((search = ft_strrchr(word, '/')))
	{
		if (word[1] == '/' && !var_get(vars, "HOME"))
		{
			tmp = ft_strndup(word + 1, search - word);
			path = ft_strjoin(var_get(vars, "HOME")->value, tmp);
			free(tmp);
		}
		else if (word[1] != '/')
		{
			tmp = ft_strndup(word + 1, search - word);
			path = ft_strjoin("/Users/", tmp);
			free(tmp);
		}
	}
	else
		path = ft_strdup("/Users/");
	return (path);
}
