/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:15:22 by user              #+#    #+#             */
/*   Updated: 2023/05/26 16:19:55 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char** argv)
{
	char **args;

	args = ft_split(argv[2],' ');
	ft_printf("\n %s \n", args[0]);
	argc = 0;
	return (0);
}