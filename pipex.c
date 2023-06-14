/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:15:22 by user              #+#    #+#             */
/*   Updated: 2023/06/14 16:21:31 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char** argv, char **envp)
{
	t_pipex pipex;

	if (argc != 5)
	{
		write(2, "Error : Wrong number of arguments\n", 34);
		return (0);
	}
	pipex = init_pipex(pipex, argv, envp);
	check_args(pipex);
	execute_command(pipex, envp);
	exit_program(pipex);
	return (0);
}