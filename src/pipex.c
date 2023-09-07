/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:06:47 by evocatur          #+#    #+#             */
/*   Updated: 2023/09/06 23:14:10 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

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
	pipex = init_pipex(pipex, argv, envp);
	check_args(pipex);
	execute_command(pipex, envp);
	exit_program(pipex, EXIT_SUCCESS);
	return (0);
}

void	check_args(t_pipex p)
{
	if (access(p.cmd1_path, F_OK) == -1 || access(p.cmd2_path, F_OK) == -1)
		exit_program(p, EXIT_FAILURE);
	if (p.in_fd == -1)
		exit_program(p, EXIT_FAILURE);
	if (access(p.filein, R_OK) == -1 || access(p.fileout, W_OK) == -1)
		exit_program(p, EXIT_FAILURE);
}

void	exit_program(t_pipex pipex, int status)
{
	free_command(pipex.cmd1);
	free_command(pipex.cmd2);
	free(pipex.cmd1_path);
	free(pipex.cmd2_path);
	if (status == EXIT_FAILURE)
		perror("Error");
	exit(status);
}

void	free_command(char **cmd)
{
	int		i;
	char	*str;

	i = 0;
	while (cmd[i])
	{
		str = cmd[i];
		free(str);
		i++;
	}
	free(cmd);
}
