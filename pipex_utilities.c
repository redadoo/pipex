/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:26:02 by evocatur          #+#    #+#             */
/*   Updated: 2023/06/10 15:20:08 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex init_pipex(t_pipex pipex, char **argv)
{
	pipex.filein = argv[1];
	pipex.fileout = argv[4];
	pipex.cmd1 = ft_split(argv[2],' ');
	pipex.cmd2 = ft_split(argv[3],' ');
	pipex.in_fd = open(pipex.filein, O_WRONLY | O_CREAT, 0777);
	pipex.out_fd = open(pipex.fileout, O_WRONLY | O_CREAT, 0777);
	pipex.cmd1_path = ft_calloc(sizeof(char) , (ft_strlen(pipex.cmd1[0]) + 6));
	pipex.cmd2_path = ft_calloc(sizeof(char) , (ft_strlen(pipex.cmd1[0]) + 6));
	ft_strlcat(pipex.cmd1_path,"/bin/",11);
	ft_strlcat(pipex.cmd2_path,"/bin/",11);
	ft_strlcat(pipex.cmd1_path,pipex.cmd1[0], (ft_strlen(pipex.cmd1[0]) + ft_strlen(pipex.cmd1_path) + 1));
	ft_strlcat(pipex.cmd2_path,pipex.cmd2[0], (ft_strlen(pipex.cmd2[0]) + ft_strlen(pipex.cmd2_path) + 1));
	// printf("\n %s  \n" , pipex.cmd1[1]);
	// printf("\n %s  \n" , pipex.cmd2[1]);
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
	close(pipex.in_fd);
	close(pipex.out_fd);
	unlink(pipex.fileout);
	unlink(pipex.filein);
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

void execute_command(t_pipex pipex)
{
	int i;
	int _fd;
	int fd[2];
	pid_t pid, wpid;
	int status = 0;
	char *str;

	i = 0;
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		dup2(pipex.out_fd, STDOUT_FILENO);
		execve(pipex.cmd1_path, pipex.cmd1, NULL);
		dup2(STDOUT_FILENO, STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	while ((wpid = wait(&status)) > 0);
	printf("so na sega \n");
	dup2(pipex.out_fd, 0);
	execve("/usr/bin/wc", pipex.cmd2, NULL);
	exit(EXIT_SUCCESS);
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

