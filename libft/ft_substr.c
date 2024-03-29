/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:46:44 by evocatur          #+#    #+#             */
/*   Updated: 2023/01/20 13:46:44 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_substr(char const *s, unsigned int start, unsigned int len)
{
	char			*newstr;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = start;
	if (!s || len < 0)
		return (NULL);
	while ((int)start < ft_strlen(s) && s[start] != '\0' && i < len)
	{
		start++;
		i++;
	}
	newstr = (char *)malloc((i + 1) * sizeof(char));
	if (!newstr)
		return (newstr);
	start = 0;
	while (start < i)
	{
		newstr[start] = s[j];
		start++;
		j++;
	}
	newstr[start] = '\0';
	return (newstr);
}
