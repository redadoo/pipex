/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:26:02 by evocatur          #+#    #+#             */
/*   Updated: 2023/06/14 16:26:28 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void first_child(int *fd, t_pipex pipex, char **env)
{
	printf("test \n");
	if (dup2(pipex.out_fd, STDIN_FILENO) != -1 && dup2(fd[1], STDOUT_FILENO) != -1)
	{
		if (execve(pipex.cmd1_path,pipex.cmd1, env) != -1)
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
}

static void second_child(int *fd, t_pipex pipex, char **env)
{
	printf("test 2 \n");
	if (dup2(pipex.out_fd, STDOUT_FILENO) != -1 && dup2(fd[0], STDIN_FILENO) != -1)
	{
		if (execve(pipex.cmd2_path,pipex.cmd2, env) != -1)
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
}

static char	*acces_command(char *cmd_name, char **paths)
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

t_pipex init_pipex(t_pipex pipex, char **argv, char **envp)
{
	pipex.filein = argv[1];
	pipex.fileout = argv[4];
	pipex.cmd1 = ft_split(argv[2],' ');
	pipex.cmd2 = ft_split(argv[3],' ');
	pipex.in_fd = open(pipex.filein, O_WRONLY | O_CREAT, 0777);
	pipex.out_fd = open(pipex.fileout, O_WRONLY | O_CREAT, 0777);
	pipex.cmd1_path = return_path(pipex.cmd1[0], pipex, envp);
	pipex.cmd2_path = return_path(pipex.cmd2[0], pipex, envp);
	return (pipex);
}

void check_args(t_pipex pipex)
{
	if (access(pipex.filein, R_OK) == -1 || access(pipex.fileout, W_OK) == -1)
	{
		exit_program(pipex);	
	}
}

void exit_program(t_pipex pipex)
{
	free_command(pipex.cmd1);
	free_command(pipex.cmd2);
	free(pipex.cmd1);
	free(pipex.cmd2);
	free(pipex.cmd1_path);
	free(pipex.cmd2_path);
	unlink(pipex.fileout);
	unlink(pipex.filein);
	exit(EXIT_SUCCESS);
}

void free_command(char **cmd)
{
	char	*str;
	int		i;

	i = 0;
	while (*cmd)
	{
		i++;
		str = *cmd;
		free(str);
		cmd++;
	}
}

void execute_command(t_pipex pipex, char**env)
{
	int		fd[2];
	int		status;
	pid_t	pid_0;
	pid_t	pid_1;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid_0 = fork();
	if (pid_0 < 0)
		exit_program(pipex);
	if (pid_0 == 0)
		first_child(fd, pipex, env);
	pid_1 = fork();
	if (pid_1 < 0)
		exit_program(pipex);
	if (pid_1 == 0)
		second_child(fd, pipex, env);
	close(fd[0]);
	close(fd[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);

}

int	file_linecount(char *file)
{
	char	c;	
	int		fd;	
	int		linecount;
	int		readcount;

	fd = open(file, O_RDONLY);
	if (!fd)
		return (-1);
	linecount = 1;
	while (true)
	{
		readcount = read(fd, &c, 1);
		if (readcount == 0)
			break ;
		if (readcount < 0)
			return (-1);
		if (c == '\n')
			linecount++;
	}
	close(fd);
	return (linecount);
}

char *return_path(char *cmd, t_pipex pipex, char**env)
{
	int		i;
	char	**paths;
	char	*cmd_path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	paths = ft_split(env[i] + 5,':');
	i = 0;
	while (paths[i])
	{
		cmd_path = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		//free(cmd_path);
		i++;
	}
	cmd_path = acces_command(cmd,paths);
	//free_command(paths);
	return (cmd_path);
}
