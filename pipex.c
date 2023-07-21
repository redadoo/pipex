/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:15:22 by user              #+#    #+#             */
/*   Updated: 2023/07/22 01:24:58 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char** argv, char **envp)
{
	t_pipex pipex;
	if (argc != 5)
	{
		write(2, "Error : Wrong number of arguments\n", 34);
		exit(EXIT_FAILURE);
	}

	if (!argv[2][0] || !argv[3][0])
	{
		write(2, "Error : command not found\n", 26);
		exit(EXIT_FAILURE);
	}
	pipex =  init_pipex(pipex, argv, envp);
 	check_args(pipex);
	execute_command(pipex, envp); 
 	exit_program(pipex, EXIT_SUCCESS);
}