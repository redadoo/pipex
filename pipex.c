/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:15:22 by user              #+#    #+#             */
/*   Updated: 2023/05/29 14:26:16 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char** argv)
{
	t_pipex pipex;

	if (argc != 5)	
		return (0);
	pipex = init_pipex(pipex, argv);
	check_args(pipex);
	//execute the comand use fork , execve , pipe
	exit_program(pipex);
	return (0);
}