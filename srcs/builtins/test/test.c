/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:48:16 by pcharrie          #+#    #+#             */
/*   Updated: 2020/01/13 17:06:23 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "utils.h"
#include "shell.h"
#include "libft.h"
#include "variables.h"
#include "builtins.h"
#include "opt.h"

int		b_test(t_cmd *cmd, t_shell *shell)
{
	(void)shell;
	if (cmd->argc == 1)
		return (1);
	if (cmd->argc == 2)
		return (!(ft_strlen(cmd->args[1]) > 0));
	if (cmd->argc == 3)
		return (!test_unary(cmd));
	if (cmd->argc == 4)
		return (!test_binary(cmd));
	ft_putendl_fd("42sh: test: too many arguments", 2);
	return (1);
}
