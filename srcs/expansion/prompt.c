/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:41:43 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/26 16:50:38 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expansion.h"

void	exec_option_prompt(char **expanded_prompt, char *to_add, int *i)
{
	char	*copy;

	copy = ft_strjoin(*expanded_prompt, to_add);
	if (ft_strcmp(*expanded_prompt, ""))
		ft_strdel(expanded_prompt);
	*expanded_prompt = ft_strdup(copy);
	ft_strdel(&copy);
	*i += 2;
}

void	handle_options_prompt(char *prompt)
{
	int		i;
	char	*expanded_prompt;

	i = 0;
	expanded_prompt = "";
	while (prompt[i])
	{
		if (prompt[i] == '\\' && prompt[i + 1] == 'u')
			exec_option_prompt(&expanded_prompt,
			var_get(g_shell.vars, "USER")->value, &i);
		else if (prompt[i] == '\\' && prompt[i + 1] == 'j')
		{
			exec_option_prompt(&expanded_prompt,
			ft_itoa((int)g_shell.jobs.len), &i);
		}
		else if (prompt[i] == '\\' && prompt[i + 1] == 'l')
		{
			exec_option_prompt(&expanded_prompt, ft_itoa(g_return), &i);
		}
		else if (prompt[i] == '\\' && prompt[i + 1] == 'v')
			exec_option_prompt(&expanded_prompt, "1.0", &i);
		else if (prompt[i] == '\\' && prompt[i + 1] == 's')
			exec_option_prompt(&expanded_prompt, "42sh", &i);
		else if (prompt[i] == '\\' && prompt[i + 1] == 'H')
			handle_options_H_prompt(&expanded_prompt, &i, 1);
		else if (prompt[i] == '\\' && prompt[i + 1] == 'h')
			handle_options_H_prompt(&expanded_prompt, &i, 0);
		else if (prompt[i] == '\\' && prompt[i + 1] == 'w')
			reduce_pwd_size(&expanded_prompt,
			var_get(g_shell.vars,"PWD")->value, &i);
		else
			add_other_char_prompt(&expanded_prompt, prompt, &i);
	}
	if (g_shell.ps1 && ft_strcmp(g_shell.ps1, ""))
		ft_strdel(&g_shell.ps1);
	g_shell.ps1 = expanded_prompt;
}

void	prompt_expansions(void)
{
	t_var	*ps1;

	ps1 = var_get(g_shell.vars, "PS1");
	if (ps1)
		handle_options_prompt(ps1->value);
	else
		g_shell.ps1 = "\033[1;31m$> \033[0m";
}
