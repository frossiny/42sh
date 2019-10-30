/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:40:21 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/30 17:29:54 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

int				handle_builtin(t_cmd *cmd, t_shell *shell);
t_builtin		get_builtin(char *name);
int				is_builtin(char *name);
int				b_env(t_cmd *cmd, t_shell *shell);
int				b_setenv(t_cmd *cmd, t_shell *shell);
int				b_unsetenv(t_cmd *cmd, t_shell *shell);
int				b_exit(t_cmd *cmd, t_shell *shell);
int				b_cd(t_cmd *cmd, t_shell *shell);
int				b_echo(t_cmd *cmd, t_shell *shell);
int				b_history(t_cmd *cmd, t_shell *shell);

#endif
