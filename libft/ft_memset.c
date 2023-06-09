/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:34:48 by evocatur          #+#    #+#             */
/*   Updated: 2023/06/09 10:04:51 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = NULL;
	p = (unsigned char *)b;
	while (len--)
	{
		*p++ = (unsigned char)c;
	}
	return (b);
}
