/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:26:56 by frossiny          #+#    #+#             */
/*   Updated: 2020/01/17 16:16:07 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include "shell.h"

void			ht_put(t_shell *shell, char *key, char *value, int increment);
char			*ht_get(t_shell *shell, char *key);
int				ht_exists(t_shell *shell, char *key);
int				ht_delone(char *key, t_shell *shell);
void			ht_delete();
int				ht_hash(size_t size, char *key);
int				ht_create(t_shell *shell, size_t size);
int				ht_can_put(char *cmd);

#endif
