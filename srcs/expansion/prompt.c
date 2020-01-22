/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:41:43 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/22 18:00:08 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void	handle_options_prompt(char *prompt)
{

	(void)prompt;
	//if (ft_strchr(prompt, "\\u"))
		
}

void	prompt_expansions(void)
{
	if (var_get(g_shell.vars, "PS1"))
		g_shell.ps1 = "lubenard - path \033[1;%dm$> \033[0m";
	else
		g_shell.ps1 = "\033[1;%dm$> \033[0m";
}
