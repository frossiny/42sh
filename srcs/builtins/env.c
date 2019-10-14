/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:27:28 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 15:13:26 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "env.h"
#include "lexer.h"
#include "utils.h"
#include "parser.h"

static int		parse_options(int *opt, int argc, char **argv)
{
	*opt = 0;
	while (argc-- > 0)
	{
		if (ft_strcmp(*argv, "--") == 0 || (*argv)[0] != '-')
			break ;
		else if (ft_strcmp(*argv, "-u") == 0
									|| ft_strcmp(*argv, "--unset") == 0)
		{
			argc--;
			argv += 2;
			continue ;
		}
		else if ((*argv)[0] == '-' && ((*argv)[1] == '\0' || (*argv)[1] == 'i'))
			*opt |= 1;
		else if ((*argv)[0] == '-' && (*argv)[1] != '\0')
		{
			ft_putstr_fd("env: illegal option -- ", 2);
			ft_putstr_fd((*argv) + 1, 2);
			ft_putchar_fd('\n', 2);
			return (0);
		}
		argv++;
	}
	return (1);
}

static void		parse_remove(t_env **env, int *argc, char ***argv)
{
	while (*argc > 0)
	{
		if ((**argv)[0] != '-' || ft_strcmp(**argv, "--") == 0)
		{
			(*argc) -= (ft_strcmp(**argv, "--") == 0);
			(*argv) += (ft_strcmp(**argv, "--") == 0);
			break ;
		}
		if (ft_strcmp(**argv, "-u") == 0 || ft_strcmp(**argv, "--unset") == 0)
		{
			(*argv)++;
			(*argc)--;
			if (*argc > 0)
				delete_env(env, **argv);
		}
		(*argc)--;
		(*argv)++;
	}
}

static void		parse_add(t_env **env, int *ac, char ***av)
{
	char	**tmp;
	char	**argv;
	int		argc;

	argc = *ac;
	argv = *av;
	while (argc > 0)
	{
		if (!ft_strchr(*argv, '='))
			break ;
		if (!(tmp = ft_strsplit(*argv, '=')))
			exit(1);
		if ((*argv)[0] == '=' || !tmp[0])
		{
			env_invalid_arg(&argc, &argv);
			ft_strddel(&tmp);
			break ;
		}
		new_envl(env, tmp[0], tmp[1], 0);
		ft_strddel(&tmp);
		argc--;
		argv++;
	}
	*ac = argc;
	*av = argv;
}

static int		exec(char *exe, char **args, t_env *env, t_shell *shell)
{
	t_cmd	*cmd;
	t_lexer	lexer;
	int		i;

	lexer.tokens = NULL;
	lexer.size = 0;
	create_token(&lexer, exe, ft_strlen(exe), TOKEN_NAME);
	i = -1;
	while (args[++i])
		create_token(&lexer, args[i], ft_strlen(args[i]), TOKEN_NAME);
	if (!(cmd = create_cmd(lexer.tokens)))
		return (1);
	cmd->allow_builtins = 0;
	g_return = execute_env(cmd, env, shell);
	free(cmd->args);
	free(cmd);
	destroy_lexer(&lexer);
	return (g_return);
}

int				b_env(t_cmd *cmd, t_shell *shell)
{
	int		options;
	t_env	*nenv;
	char	**args;

	if (cmd->argc == 1)
		return (disp_env(shell->env));
	args = cmd->args;
	if (!parse_options(&options, --cmd->argc, ++args))
		return (1);
	nenv = dup_env(shell->env, options);
	parse_remove(&nenv, &(cmd->argc), &args);
	parse_add(&nenv, &(cmd->argc), &args);
	if (cmd->argc < 1)
		return (disp_free_env(&nenv));
	exec(*args, args + 1, nenv, shell);
	free_env(&nenv);
	return (g_return);
}
