/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:06:47 by evocatur          #+#    #+#             */
/*   Updated: 2023/07/26 16:31:32 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	int i;
	t_ppbx pipex;

	i = 0;
	if (argc < 5)
		return (0);
	pipex.filein = argv[1];
	pipex.fileout = argv[argc - 1];
	pipex.in_fd = open(pipex.filein, O_RDONLY);
	pipex.out_fd = open(pipex.fileout, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	pipex.cmd_number = argc - 4;
	if (access(pipex.filein, R_OK) == -1 || access(pipex.fileout, W_OK) == -1)
		exit_bonus(pipex, EXIT_FAILURE);
	if (pipe(pipex.pipe) == -1)
		exit_bonus(pipex, EXIT_FAILURE);
	pipex.cmd = ft_split(argv[i + 2], ' ');
	while (i < pipex.cmd_number)
	{
		exe_cmd_bonus(pipex, i, argv, envp);		
		i++;
	}
	close(pipex.pipe[0]);
	close(pipex.pipe[1]);
	waitpid(-1, NULL, 0);
}
static void	sub_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

void	exe_cmd_bonus(t_ppbx pipex, int i, char**argv,char **envp)
{
	if (i == 0)
	{
		pipex.pid = fork();
		if (pipex.pid < 0)
			exit_bonus(pipex,EXIT_FAILURE);
		if (pipex.pid == 0)
		{
			sub_dup2(pipex.in_fd, pipex.pipe[1]);
			close(pipex.pipe[0]);
			pipex.cmd = ft_split(argv[i + 2], ' ');
			pipex.cmd_path = return_path(pipex.cmd[0], envp);
			execve(pipex.cmd_path, pipex.cmd, envp);
		}
	}
	else if (i % 2 != 0 && i < pipex.cmd_number - 1)
	{
		pipex.pid = fork();
		if (pipex.pid < 0)
			exit_bonus(pipex,EXIT_FAILURE);
		if (pipex.pid == 0)
		{
			sub_dup2(pipex.pipe[1], pipex.pipe[0]);
			pipex.cmd = ft_split(argv[i + 2], ' ');
			pipex.cmd_path = return_path(pipex.cmd[0], envp);
			execve(pipex.cmd_path, pipex.cmd, envp);
		}
	}
	else if (i % 2 != 1 && i < pipex.cmd_number - 1)
	{
		pipex.pid = fork();
		if (pipex.pid < 0)
			exit_bonus(pipex,EXIT_FAILURE);
		if (pipex.pid == 0)
		{
			sub_dup2(pipex.pipe[0], pipex.pipe[1]);
			pipex.cmd = ft_split(argv[i + 2], ' ');
			pipex.cmd_path = return_path(pipex.cmd[0], envp);
			execve(pipex.cmd_path, pipex.cmd, envp);
		}
	}
	else if (i == pipex.cmd_number - 1)
	{
		pipex.pid = fork();
		if (pipex.pid < 0)
			exit_bonus(pipex,EXIT_FAILURE);
		if (pipex.pid == 0)
		{
			if (pipex.cmd_number % 2 != 0)
				sub_dup2(pipex.pipe[1], pipex.out_fd);
			else
				sub_dup2(pipex.pipe[0], pipex.out_fd);
			close(pipex.pipe[0]);
			pipex.cmd = ft_split(argv[i + 2], ' ');
			pipex.cmd_path = return_path(pipex.cmd[0], envp);
			execve(pipex.cmd_path, pipex.cmd, envp);
		}
	}
}
