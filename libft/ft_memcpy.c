/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:48:37 by evocatur          #+#    #+#             */
/*   Updated: 2023/10/22 18:28:39 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*copy1;
	char			*copy2;
	unsigned int	i;

	copy1 = (char *)src;
	copy2 = (char *)dst;
	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i != n)
	{
		copy2[i] = copy1[i];
		i++;
	}
	return (dst);
}
