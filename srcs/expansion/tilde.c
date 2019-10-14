/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:49:15 by frossiny          #+#    #+#             */
/*   Updated: 2019/08/12 18:31:09 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int	handle_home_spec(t_token *token, t_env *env)
{
	char	*path;
	t_env	*var;

	if (!env || token->content[1] == '\0')
		return (0);
	if ((token->content[1] == '+' || token->content[1] == '-')
			&& (token->content[2] == '\0' || token->content[2] == '/'))
	{
		if (!(var = get_enve(env, token->content[1] == '+'
					? "PWD" : "OLDPWD")))
			return (0);
		if (!(path = ft_strjoin(var->value, token->content + 2)))
			return (0);
	}
	else
		return (0);
	free(token->content);
	token->content = path;
	return (1);
}

static int	handle_home_own(t_token *token, t_env *env)
{
	char	*path;
	t_env	*tmp;

	if (!env)
		return (0);
	path = NULL;
	if ((tmp = get_enve(env, "HOME")))
		path = ft_strjoin(tmp->value, token->content + 1);
	else if ((tmp = get_enve(env, "USER")))
		path = ft_strjoint("/Users/", tmp->value, token->content + 1);
	if (!path && !(path = ft_strdup("")))
		return (0);
	free(token->content);
	token->content = path;
	return (1);
}

int			handle_home(t_token *token, t_env *env)
{
	char	*path;

	path = NULL;
	if (!token)
		return (0);
	if (token->content[1] == '\0' || token->content[1] == '/')
		return (handle_home_own(token, env));
	else if (token->content[1] == '+' || token->content[1] == '-')
		return (handle_home_spec(token, env));
	else if (!ft_isalnum(token->content[1]))
		return (1);
	else
	{
		path = ft_strjoin("/Users/", token->content + 1);
		if (!path || access(path, F_OK))
		{
			path ? no_user(token->content + 1) : 0;
			ft_strdel(&path);
			return (0);
		}
	}
	path = path ? path : ft_strdup("");
	free(token->content);
	token->content = path;
	return (1);
}
