/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:41:10 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/15 14:45:09 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "shell.h"

void	prompt(void)
{
	if (!isatty(0))
		return ;
	if (g_ignore_signals == 0)
		ft_printf("\033[1;%dm$> \033[0m", g_return ? 31 : 32);
	else if (g_ignore_signals == 1)
		ft_printf("quote> ");
	else if (g_ignore_signals == 2)
		ft_printf("dquote> ");
	else if (g_ignore_signals == 3)
		ft_printf("> ");
}

int		prompt_len(void)
{
	if (g_ignore_signals == 0)
		return (ft_strlen("$> "));
	else if (g_ignore_signals == 1)
		return (ft_strlen("quote> "));
	else if (g_ignore_signals == 2)
		return (ft_strlen("dquote> "));
	else if (g_ignore_signals == 3)
		return (ft_strlen("> "));
	return (0);
}
