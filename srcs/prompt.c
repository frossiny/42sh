/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:41:10 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/26 18:35:34 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "shell.h"
#include "jobcontrol.h"

void	prompt(void)
{
	if (!isatty(0))
		return ;
	if (g_ignore_signals == 0)
	{
		prompt_expansions();
		ft_putstr(g_shell.ps1);
	//ft_printf(g_shell.ps1);//,g_return ? 31 : 32);
	}
	else if (g_ignore_signals == 1)
		ft_printf("> ");
}

int		prompt_len(void)
{
	if (g_ignore_signals == 0)
		return (ft_strlen(g_shell.ps1));
	else if (g_ignore_signals == 1)
		return (ft_strlen("> "));
	return (0);
}
