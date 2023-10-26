/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:46:40 by evocatur          #+#    #+#             */
/*   Updated: 2023/10/26 17:26:38 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_pipex	*init_pipex(char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	pipex->status = 0;
	pipex->filein = argv[1];
	pipex->fileout = argv[4];
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	pipex->in_fd = open(pipex->filein, O_RDONLY);
	pipex->out_fd = open(pipex->fileout, O_TRUNC | O_CREAT | O_RDWR, 0000644);

	if (is_path(pipex->cmd1[0]) == 1)
		pipex->cmd1_path = ft_strdup(pipex->cmd1[0]);
	else
		pipex->cmd1_path = return_path(pipex->cmd1[0], envp);
	
	if (is_path(pipex->cmd2[0]) == 1)
		pipex->cmd2_path = ft_strdup(pipex->cmd2[0]);
	else
		pipex->cmd2_path = return_path(pipex->cmd2[0], envp);

	return (pipex);
}

void	execute_command(t_pipex *pipex, char **env)
{
	if (pipe(pipex->pipe) == -1)
		exit(EXIT_FAILURE);
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		exit_program(pipex, EXIT_FAILURE);
	if (pipex->pid1 == 0)
		first_child(pipex, env);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		exit_program(pipex, EXIT_FAILURE);
	if (pipex->pid2 == 0)
		second_child(pipex, env);
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
}

void	first_child(t_pipex *pipex, char **env)
{
	dup2(pipex->pipe[1], STDOUT_FILENO);
	dup2(pipex->in_fd, STDIN_FILENO);
	close(pipex->pipe[0]);
	execve(pipex->cmd1_path, pipex->cmd1, env);
	exit_program(pipex, EXIT_FAILURE);
}

void	second_child(t_pipex *pipex, char **env)
{
	dup2(pipex->out_fd, STDOUT_FILENO);
	dup2(pipex->pipe[0], STDIN_FILENO);
	close(pipex->pipe[1]);
	execve(pipex->cmd2_path, pipex->cmd2, env);
	exit_program(pipex, EXIT_FAILURE);
}
