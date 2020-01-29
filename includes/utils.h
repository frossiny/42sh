/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:30:04 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/28 19:51:38 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structs.h"

int					is_escaped(char *s, size_t index, int endquote);

int					is_local_exe(char *name);
int					is_relative_path(char *name);
char				*format_path_exe(char *dir, char *file);
int					cd_is_dir(char *file, char *name);
int					can_execute(char *path, t_shell *shell, int verbose);
void				copy_tab(int op[], int np[]);

void				inexistant(char *name);
void				not_found(char *name);
int					permission_denied(char *name);
void				no_user(char *name);
int					cd_exists(char *file, char *name);
void				env_invalid_arg(int *argc, char ***argv);
int					is_directory_err(char *name, int verbose);

void				u_free_shell(int kill_jobs);

char				*extract_first(char *command, char stop);

#endif
