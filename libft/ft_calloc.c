/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:19:42 by evocatur          #+#    #+#             */
/*   Updated: 2023/06/09 10:04:51 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*s;

	s = malloc(count * size);
	if (!s)
		return (NULL);
	i = 0;
	ft_bzero(s, size * count);
	return (s);
}
