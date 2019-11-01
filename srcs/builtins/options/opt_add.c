/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:20:21 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/16 16:20:31 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "opt.h"

t_opt		*opt_add(t_options *opts, char *name, char *value)
{
	t_opt	*new;
	t_opt	*curr;

	if (!(new = (t_opt *)malloc(sizeof(t_opt))))
		return (NULL);
	new->opt = ft_strdup(name);
	new->value = value ? ft_strdup(value) : NULL;
	new->next = NULL;
	if (opts->opts)
	{
		curr = opts->opts;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	else
		opts->opts = new;
	return (new);
}
