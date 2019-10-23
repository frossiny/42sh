/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:08:55 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/23 20:06:51 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "lexer.h"

static int	is_aggr_valid(t_parser *par)
{
	if (par->tokens->type != TOKEN_AGGR)
		return (1);
	if (!par->tokens->next)
		return (0);
	if (!ft_strisdigit(par->tokens->next->content) && !ft_strequ(par->tokens->next->content, "-"))
	{
		par_next(par, 1);
		return (0);
	}
	return (1);
}

int		par_type_redir(t_parser *par)
{
	if (!tok_is_word(par->tokens->next))
	{
		par_next(par, 1);
		return (0);
	}
	if (!is_aggr_valid(par))
		return (0);
	par_next(par, 1);
	return (1);
}

int		par_type_io_fd(t_parser *par)
{
	if (par->tokens->next == NULL)
	{
		par->tokens->type = TOKEN_NAME;
		return (1);
	}
	if (!tok_is_redirection(par->tokens->next))
	{
		par_next(par, 1);
		return (0);
	}
	par_next(par, 1);
	if (!tok_is_word(par->tokens->next))
	{
		par_next(par, 1);
		return (0);
	}
	par_next(par, 1);
	return (1);
}
