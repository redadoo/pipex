/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:14:15 by evocatur          #+#    #+#             */
/*   Updated: 2023/06/09 10:04:52 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	char	*copydst;
	char	*src_start;
	size_t	copydst_len;
	size_t	remaing;

	copydst = dest;
	src_start = (char *) src;
	remaing = size;
	while (remaing-- != 0 && *copydst != '\0')
		copydst++;
	copydst_len = copydst - dest;
	remaing = size - copydst_len;
	if (remaing == 0)
		return (copydst_len + ft_strlen((char *) src));
	while (*src != '\0')
	{
		if (remaing > 1)
		{
			*copydst++ = *src;
			remaing--;
		}
		src++;
	}
	*copydst = '\0';
	return (copydst_len + (src - src_start));
}
