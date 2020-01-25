/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:41:43 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/25 17:13:26 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

char	*stradd(char *s1, char s2)
{
	char	*dst;
	int		i;

	i = 0;
	if (!s1 || !s2 || !(dst = ft_strnew(ft_strlen(s1) + 1)))
		return (NULL);
	ft_strcpy(dst, s1);
	dst[ft_strlen(s1)] = s2;
	return (dst);
}

char	*reduce_pwd_size(char *pwd)
{
	t_var	*home;
	char	*extracted;

	if (!(home = var_get(g_shell.vars, "HOME")))
		return (pwd);
	if (ft_strstr(pwd, home->value))
	{
		extracted = ft_strsub(pwd, ft_strlen(home->value), ft_strlen(pwd) -
		ft_strlen(home->value));
		return (ft_strjoin("~", extracted));
	}
	return (pwd);
}

void	exec_option_prompt(char **expanded_prompt, char *to_add, int *i)
{
	*expanded_prompt = ft_strjoin(*expanded_prompt, to_add);
	*i += 2;
}


char	*extract_first(char *command, char stop)
{
	int		i;

	i = 0;
	while (command[i] != stop && command[i])
		++i;
	return (ft_strsub(command, 0, i));
}

void	handle_options_H_prompt(char **expanded_prompt, int *i, int mode)
{
	char	*first_point;

	gethostname(hostname, 4096);
	if (mode == 1)
		exec_option_prompt(&expanded_prompt, hostname, &i);
	else
	{
		first_point = extract_first(hostname, ".");
		exec_option_prompt(&expanded_prompt, first_point, &i);
		ft_strdel(&first_point);
	}
}

void	handle_options_prompt(char *prompt)
{
	int		i;
	char	*expanded_prompt;
	char	hostname[4096];

	i = 0;
	expanded_prompt = "";
	while (prompt[i])
	{
		if (prompt[i] == '\\' && prompt[i + 1] == 'u')
			exec_option_prompt(&expanded_prompt,
			var_get(g_shell.vars, "USER")->value, &i);
		else if (prompt[i] == '\\' && prompt[i + 1] == 'j')
			exec_option_prompt(&expanded_prompt,
			ft_itoa((int)g_shell.jobs.len), &i);
		else if (prompt[i] == '\\' && prompt[i + 1] == 'l')
			exec_option_prompt(&expanded_prompt, ft_itoa(g_return), &i);
		else if (prompt[i] == '\\' && prompt[i + 1] == 'v')
			exec_option_prompt(&expanded_prompt, "1.0", &i);
		else if (prompt[i] == '\\' && prompt[i + 1] == 's')
			exec_option_prompt(&expanded_prompt, "42sh", &i);
		else if (prompt[i] == '\\' && prompt[i + 1] == 'H')
			handle_options_H_prompt(&expanded_prompt, &i, 1);
		else if (prompt[i] == '\\' && prompt[i + 1] == 'h')
			handle_options_H_prompt(&expanded_prompt, &i, 0);
		else if (prompt[i] == '\\' && prompt[i + 1] == 'w')
		{
			exec_option_prompt(&expanded_prompt, reduce_pwd_size(
			var_get(g_shell.vars,"PWD")->value), &i);
		}
		else
			expanded_prompt = stradd(expanded_prompt, prompt[i++]);
	}
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
