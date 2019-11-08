/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:20:40 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/16 16:22:13 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opt.h"

void	opt_free(t_options *options)
{
	t_opt	*curr;
	t_opt	*next;

	curr = options->opts;
	while (curr)
	{
		next = curr->next;
		free(curr->opt);
		free(curr->value);
		free(curr);
		curr = next;
	}
	free(options);
}
