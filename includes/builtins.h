/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:40:21 by frossiny          #+#    #+#             */
/*   Updated: 2019/11/08 17:13:20 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"

t_builtin	get_builtin(char *name);
int			is_builtin(char *name);

/*
** Builtins functions
*/
int			handle_builtin(t_cmd *cmd, t_shell *shell);
int			b_set(t_cmd *cmd, t_shell *shell);
int			b_unset(t_cmd *cmd, t_shell *shell);
int			b_exit(t_cmd *cmd, t_shell *shell);
int			b_cd(t_cmd *cmd, t_shell *shell);
int			b_echo(t_cmd *cmd, t_shell *shell);
int			b_export(t_cmd *cmd, t_shell *shell);
int			b_history(t_cmd *cmd, t_shell *shell);

/*
** Cd internal functions
*/
char		*cd_buildpath(char *path);

/*
** history internal functions
*/
void		parse_and_add_hist(t_cmd *cmd, t_shell *shell);
void		empty_hist(t_shell *shell);

#endif
