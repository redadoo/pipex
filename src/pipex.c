/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 09:57:26 by evocatur          #+#    #+#             */
/*   Updated: 2023/10/26 17:34:58 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

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

	pipex = init_pipex(argv, envp);
	check_args(pipex);
	execute_command(pipex, envp);
	exit_program(pipex, EXIT_SUCCESS);
	return (1);
}

void	check_args(t_pipex *p)
{
	if (access(p->cmd1_path, F_OK) == -1)
	{
		p->status = 127;
		write(2, p->cmd1[0],ft_strlen(p->cmd1[0]));
		write(2, "command not found\n", 19);
	}
	if (access(p->cmd2_path, F_OK) == -1)
	{
		p->status = 127;
		write(2, p->cmd2[0],ft_strlen(p->cmd2[0]));
		write(2, "command not found\n", 19);
	}
	if (p->in_fd == -1)
		perror("");
	if (p->out_fd == -1)
		perror("");
}

void	exit_program(t_pipex *pipex, int status)
{
	int s = pipex->status;

	if (pipex->cmd1)
		free_command(pipex->cmd1);
	if (pipex->cmd2)
		free_command(pipex->cmd2);
	if (pipex->cmd1_path)
		free(pipex->cmd1_path);
	if (pipex->cmd2_path)
		free(pipex->cmd2_path);
	if (pipex->status != 0)
	{
		free(pipex);
		exit(s);
	}
	free(pipex);
	exit(status);
}
