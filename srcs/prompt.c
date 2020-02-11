/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:41:10 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/29 17:00:51 by lubenard         ###   ########.fr       */
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
	}
	else if (g_ignore_signals == 1)
		ft_printf("> ");
}

int		count_len_prompt(char *ps1)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (ps1[i])
	{
		if (ps1[i] == 27 && !ft_strnncmp(ps1, "[3", i + 1, i + 2)
		&& ps1[i + 4] == 'm')
			i += 5;
		else if (ps1[i] == 27 && !ft_strnncmp(ps1, "[0m", i + 1, i + 2))
			i += 4;
		else if (ps1[i] == 27 && !ft_strnncmp(ps1, "[1;3", i + 1, i + 4)
		&& ps1[i + 6] == 'm')
			i += 7;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

int		prompt_len(void)
{
	if (g_ignore_signals == 0)
		return (count_len_prompt(g_shell.ps1));
	else if (g_ignore_signals == 1)
		return (ft_strlen("> "));
	return (0);
}
