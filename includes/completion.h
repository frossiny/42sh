/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:47:31 by alagroy-          #+#    #+#             */
/*   Updated: 2019/11/14 19:39:44 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLETION_H
# define COMPLETION_H
# include <dirent.h>
# include "libft.h"
# include "lexer.h"
# include "shell.h"
# include "structs.h"
# include "termcaps.h"
# define CMD 1
# define FILE 2
# define VAR 3

typedef struct dirent	t_dirent;

int						lite_parser(t_cursor_pos *pos);
t_list					*compl_file(char *compl, t_shell *shell);
t_list					*compl_cmd(char *compl, t_shell *shell);
t_list					*compl_var(char *compl, t_shell *shell);
t_list					*find_file(char *path, char *file);

#endif
