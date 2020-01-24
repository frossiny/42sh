/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:41:43 by lubenard          #+#    #+#             */
/*   Updated: 2020/01/24 09:39:23 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

char	*stradd(char *s1, char s2)
{
	char	*dst;

	if (!s1 || !s2 || !(dst = ft_strnew(ft_strlen(s1) + 1)))
		return (NULL);
	ft_strcpy(dst, s1);
	dst[ft_strlen(s1) + 1] = s2;
	return (dst);

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
		{
			expanded_prompt = ft_strjoin(expanded_prompt, var_get(g_shell.vars,
			"USER")->value);
			//ft_printf("expanded prompt is |%s|\n", expanded_prompt);
			i += 2;
		}
		else if (prompt[i] == '\\' && prompt[i + 1] == 'j')
		{
			expanded_prompt = ft_strjoin(expanded_prompt,
			ft_itoa((int)g_shell.jobs.len));
			//ft_printf("expanded prompt is |%s|\n", expanded_prompt);
			i += 2;
		}
		else if (prompt[i] == '\\' && prompt[i + 1] == 'v')
		{
			//ft_printf("expanded_prompt in v = %s\n", expanded_prompt);
			expanded_prompt = ft_strjoin(expanded_prompt, "1.0");
			//ft_printf("expanded prompt is |%s|\n", expanded_prompt);
			i += 2;
		}
		else if (prompt[i] == '\\' && prompt[i + 1] == 's')
		{
			expanded_prompt = ft_strjoin(expanded_prompt, "42sh");
			//ft_printf("expanded prompt is |%s|\n", expanded_prompt);
			i += 2;
		}
		else if (prompt[i] == '\\' && prompt[i + 1] == 'H')
		{
			gethostname(hostname, 4096);
			expanded_prompt = ft_strjoin(expanded_prompt,
			hostname);
			//ft_printf("expanded prompt is |%s|\n", expanded_prompt);
			i += 2;
		}
		else
			expanded_prompt = stradd(expanded_prompt, prompt[i++]);
	}
	//ft_printf("expanded prompt is |%s|\n", expanded_prompt);
	g_shell.ps1 = expanded_prompt;
}

void	prompt_expansions(void)
{
	t_var	*ps1;

	ps1 = var_get(g_shell.vars, "PS1");
	if (ps1)
		handle_options_prompt(ps1->value);
	else
		g_shell.ps1 = "\033[1;%dm$> \033[0m";
}
