/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:40:51 by vsaltel           #+#    #+#             */
/*   Updated: 2020/01/22 15:21:29 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "shell.h"

# include "structs.h"
# include "expansion.h"

void				free_history(t_history *history);
void				memset_history(t_history *history);
void				get_history(void);
void				overwrite_history(t_histo_lst *histo);
t_histo_lst			*new_link(char *str);
void				add_to_history(char *str, t_history *history);
char				*exp_sub_pattern(char *str, int i, int type);
void				maj_last_index(t_expansion *e, char *needle);
int					histo_cmp(const char *s1, const char *s2);
int					histo_expansion(t_shell *shell, char **input);

#endif
