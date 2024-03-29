/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:19:23 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/11/27 19:26:37 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

long		ft_hash(char *str)
{
	long	hash;
	int		i;

	i = 0;
	hash = 1337;
	while (str[i])
		hash = ((hash << 5) + hash) + str[i++];
	return (hash);
}
