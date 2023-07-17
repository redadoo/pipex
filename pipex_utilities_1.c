/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilities_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:26:02 by evocatur          #+#    #+#             */
/*   Updated: 2023/06/19 13:38:36 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(int *fd, t_pipex pipex, char **env)
{
	if (dup2(fd[1], STDOUT_FILENO) != -1 && dup(pipex.in_fd) != -1)
	{
   		if(execve(pipex.cmd1_path, pipex.cmd1, env) != -1)
		{
			exit(EXIT_SUCCESS);
		}
		else
			exit_program(pipex, EXIT_FAILURE); 
	}
	exit_program(pipex, EXIT_FAILURE);
}

void	second_child(int *fd, t_pipex pipex, char **env)
{
 	if (dup2(fd[0], STDIN_FILENO) != -1 && dup2(pipex.out_fd, STDOUT_FILENO) != -1 )
	{
 		if(execve(pipex.cmd2_path, pipex.cmd2, env) != -1)
			exit(EXIT_SUCCESS);
		else
			exit(EXIT_FAILURE);
	}
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
	int		fd[2];
	int		status;
	pid_t	pid_0;
	pid_t	pid_1;

	status = 0;
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid_0 = fork();
	if (pid_0 < 0)
		exit_program(pipex, EXIT_FAILURE);
	if (pid_0 == 0)
		first_child(fd, pipex, env);
	pid_1 = fork();
	if (pid_1 < 0)
		exit_program(pipex, EXIT_FAILURE);
	if (pid_1 == 0)
		second_child(fd, pipex, env);
	close(fd[0]);
	close(fd[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
}
