/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:43:55 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/16 13:59:20 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_var	*var_new(char *key, char *value, int export)
{
	t_var	*nvar;

	if (!key)
		return (NULL);
	if (!(nvar = (t_var *)malloc(sizeof(t_var))))
		return (NULL);
	if (!(nvar->key = ft_strdup(key)) || !(nvar->value = ft_strdup(value)))
	{
		free(nvar);
		return (NULL);
	}
	nvar->export = export;
	nvar->next = NULL;
	return (nvar);
}
