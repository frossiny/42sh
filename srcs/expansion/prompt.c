/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:41:43 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/29 11:35:11 by lubenard         ###   ########.fr       */
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

int		color_prompt(char **expanded_prompt, char *prompt, int *i)
{
	if (!ft_strnncmp(prompt, "{red}", *i, *i + 3))
		return (color_utils(expanded_prompt, RED, i, 3));
	if (!ft_strnncmp(prompt, "{white}", *i, *i + 5))
		return (color_utils(expanded_prompt, WHITE, i, 5));
	if (!ft_strnncmp(prompt, "{cyan}", *i, *i + 4))
		return (color_utils(expanded_prompt, CYAN, i, 4));
	if (!ft_strnncmp(prompt, "{blue}", *i, *i + 4))
		return (color_utils(expanded_prompt, BLUE, i, 4));
	if (!ft_strnncmp(prompt, "{black}", *i, *i + 5))
		return (color_utils(expanded_prompt, BLACK, i, 5));
	if (!ft_strnncmp(prompt, "{green}", *i, *i + 5))
		return (color_utils(expanded_prompt, GREEN, i, 5));
	if (!ft_strnncmp(prompt, "{brown}", *i, *i + 5))
		return (color_utils(expanded_prompt, BROWN, i, 5));
	if (!ft_strnncmp(prompt, "{purple}", *i, *i + 6))
		return (color_utils(expanded_prompt, PURPLE, i, 6));
	if (!ft_strnncmp(prompt, "{lgray}", *i, *i + 5))
		return (color_utils(expanded_prompt, LGRAY, i, 5));
	return (0);
}

void	prompt_main_loop(char *prompt, int *i, char **expanded_prompt)
{
	while (prompt[*i])
	{
		if (prompt[*i] == '\\' && prompt[*i + 1] == 'u')
			exec_option_prompt(expanded_prompt,
			var_get(g_shell.vars, "USER")->value, i);
		else if (prompt[*i] == '\\' && prompt[*i + 1] == 'j')
			handle_options_num_prompt(expanded_prompt,
			(int)g_shell.jobs.len, i);
		else if (prompt[*i] == '\\' && prompt[*i + 1] == 'l')
			handle_options_num_prompt(expanded_prompt, g_return, i);
		else if (prompt[*i] == '\\' && prompt[*i + 1] == 'v')
			exec_option_prompt(expanded_prompt, "1.0", i);
		else if (prompt[*i] == '\\' && prompt[*i + 1] == 's')
			exec_option_prompt(expanded_prompt, "42sh", i);
		else if (prompt[*i] == '\\' && prompt[*i + 1] == 'H')
			handle_options_h_prompt(expanded_prompt, i, 1);
		else if (prompt[*i] == '\\' && prompt[*i + 1] == 'h')
			handle_options_h_prompt(expanded_prompt, i, 0);
		else if (prompt[*i] == '\\' && prompt[*i + 1] == 'w')
			reduce_pwd_size(expanded_prompt,
			var_get(g_shell.vars, "PWD")->value, i);
		else
			add_other_char_prompt(expanded_prompt, prompt, i);
	}
}

void	handle_options_prompt(char *prompt)
{
	int		i;
	char	*expanded_prompt;

	i = 0;
	expanded_prompt = "";
	prompt_main_loop(prompt, &i, &expanded_prompt);
	exec_option_prompt(&expanded_prompt, WHITE, &i);
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
