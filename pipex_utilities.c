/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:26:02 by evocatur          #+#    #+#             */
/*   Updated: 2023/06/05 18:12:23 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex init_pipex(t_pipex pipex, char **argv)
{
	pipex.filein = argv[1];
	pipex.fileout = argv[4];
	pipex.cmd1 = ft_split(argv[2],' ');
	pipex.cmd2 = ft_split(argv[3],' ');
	pipex.in_fd = open(pipex.filein, O_WRONLY | O_CREAT, 0644);
	pipex.out_fd = open(pipex.fileout, O_WRONLY | O_CREAT, 0644);
	pipex.cmd1_path = ft_calloc(sizeof(char) , (ft_strlen(pipex.cmd1[0]) + 10));
	pipex.cmd2_path = ft_calloc(sizeof(char) , (ft_strlen(pipex.cmd1[0]) + 10));
	ft_strlcat(pipex.cmd1_path,"/usr/bin/",11);
	ft_strlcat(pipex.cmd2_path,"/usr/bin/",11);
	ft_strlcat(pipex.cmd1_path,pipex.cmd1[0], (ft_strlen(pipex.cmd1[0]) + ft_strlen(pipex.cmd1_path) + 1));
	ft_strlcat(pipex.cmd2_path,pipex.cmd2[0], (ft_strlen(pipex.cmd2[0]) + ft_strlen(pipex.cmd2_path) + 1));
	//printf("\n%i\n",ft_strlen(pipex.cmd2_path));
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
	int fd[2];
	int _fd;
	int i;
	pid_t pid;
	char *str;

	i = 0;
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		close(fd[0]);
		execve(pipex.cmd1_path, pipex.cmd1, NULL);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(NULL);
		execve(pipex.cmd2_path, pipex.cmd2, NULL);
		close(fd[1]);
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	// if (pid == 0)
	// {
	// 	close(fd[0]);
	// 	 execve(pipex.cmd1_path, pipex.cmd1, NULL);
	// 	 _fd = open(pipex.fileout, O_RDONLY);
	// 	 while (i < file_linecount(pipex.fileout))
	// 	 {
	// 	 	str = get_next_line(_fd);
	// 		printf(" %s  \n",str);
	// 	 	write(fd[1],str,ft_strlen(str));
	// 	 	i++;
	// 	 }
	// 	// //passare nella pipe outfile al cm2
	// 	close(fd[1]);
	// 	exit(EXIT_SUCCESS);
	// }
	// else
	// {
	// 	close(fd[1]);
	// 	//_fd = open(pipex.fileout, O_RDONLY);
	// 	//read(fd[0],str,ft_strlen(get_next_line(_fd)));
	// 	//printf(" %s  \n",str);
	// 	i++;
	// 	close(fd[0]);
	// 	exit(EXIT_SUCCESS);
	// }
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

