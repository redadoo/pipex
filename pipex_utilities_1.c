/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilities_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:26:02 by evocatur          #+#    #+#             */
/*   Updated: 2023/07/22 01:34:15 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex pipex, char **env)
{
	dup2(pipex.pipe[1], STDOUT_FILENO);
	dup2(pipex.in_fd, STDIN_FILENO);
	close(pipex.pipe[0]);
	execve(pipex.cmd1_path, pipex.cmd1, env);
	exit_program(pipex, EXIT_FAILURE);
}

void	second_child(t_pipex pipex, char **env)
{
	dup2(pipex.out_fd, STDOUT_FILENO);
	dup2(pipex.pipe[0],STDIN_FILENO);
	close(pipex.pipe[1]);
	execve(pipex.cmd2_path, pipex.cmd2, env);
  	exit_program(pipex, EXIT_FAILURE); 
}

char	*acces_command(char *cmd_name, char **paths)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd_name);
		if (access(cmd_path, X_OK) == 0)
			break ;
		i++;
	}
	return (cmd_path);
}

void	execute_command(t_pipex pipex, char**env)
{
	int		status;

	status = 0;
	if (pipe(pipex.pipe) == -1)
		exit(EXIT_FAILURE);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		exit_program(pipex, EXIT_FAILURE);
	if (pipex.pid1 == 0)
		first_child(pipex, env);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		exit_program(pipex, EXIT_FAILURE);
	if (pipex.pid2 == 0)
		second_child(pipex, env);
	close(pipex.pipe[0]);
	close(pipex.pipe[1]);
	waitpid(pipex.pid1, NULL, 0);		
	waitpid(pipex.pid2, NULL, 0);		
}
