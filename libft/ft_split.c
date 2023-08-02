/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:33:05 by evocatur          #+#    #+#             */
/*   Updated: 2023/08/02 14:56:06 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../pipex_bonus.h"

static size_t	lens(char *str, char div)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		if (*str != div)
		{
			++i;
			while (*str && *str != div)
				++str;
		}
		else
			++str;
	}
	return (i + 1);
}

char	**ft_split(const char *s, char c)
{
	char	**newstr;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	i = 0;
	newstr = (char **)ft_calloc(lens((char *)s, c), sizeof(char *));
	if (!newstr)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			j = 0;
			while (*s && *s != c && ++j)
				++s;
			newstr[i] = ft_substr(s - j, 0, j);
			i++;
		}
		else
			++s;
	}
	return (newstr);
}
