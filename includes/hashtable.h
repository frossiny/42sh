/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:26:56 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 14:55:51 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

#include "structs.h"

void			ht_put(t_shell *shell, char *key, char *value);
char			*ht_get(t_shell *shell, char *key);
int				ht_exists(t_shell *shell, char *key);
int				ht_delone(char *key, t_shell *shell);
void			ht_delete();
int				ht_hash(size_t size, char *key);
int				ht_create(t_shell *shell, size_t size);

#endif
