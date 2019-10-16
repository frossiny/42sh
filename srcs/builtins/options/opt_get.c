/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:36:43 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/16 16:45:24 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "opt.h"

t_opt	*opt_get(t_options *options, char *name)
{
	t_opt	*curr;

	curr = options->opts;
	while (curr)
	{
		if (ft_strequ(curr->opt, name))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
