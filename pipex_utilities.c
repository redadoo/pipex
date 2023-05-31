/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:26:02 by evocatur          #+#    #+#             */
/*   Updated: 2023/05/31 14:31:46 by user             ###   ########.fr       */
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
	pipex.cmd1_path = "/usr/bin/";
	//ft_strlcat(pipex.cmd1_path,pipex.cmd1[0]);
	//ft_strlcat(pipex.cmd1_path,pipex.cmd1[0]);
	return (pipex);
}

void check_args(t_pipex pipex)
{
	if (access(pipex.filein, R_OK) == -1 || access(pipex.fileout, W_OK) == -1)
	{
		exit_program(pipex);	
	}
	dup2(pipex.in_fd,  STDIN_FILENO);
	dup2(pipex.out_fd, STDOUT_FILENO);
}

void exit_program(t_pipex pipex)
{
	free_command(pipex.cmd1);
	free_command(pipex.cmd2);
	free(pipex.cmd1);
	free(pipex.cmd2);
	close(pipex.in_fd);
	close(pipex.out_fd);
	//unlink(pipex.fileout);
	//unlink(pipex.filein);
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
	pid_t pid;
	char buffer[13];

	//fare il redirect con la pipe del output di cmd1 su cmd2
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		close(fd[0]); // close the read end of the pipe
		//execve("/bin/ls", pipex.cmd1, NULL);
		write(fd[1], "luca", 4);
		close(fd[1]); // close the write end of the pipe
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]); // close the write end of the pipe
		execve("/usr/bin/wc", pipex.cmd2, NULL);
		read(fd[0], buffer, 4);
		close(fd[0]); // close the read end of the pipe
		printf("Message from child: '%s' \n", buffer);
		exit(EXIT_SUCCESS);
	}
	//execve("/bin/ls", pipex.cmd1, NULL);
	//execve("/usr/bin/wc", pipex.cmd2, NULL);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	char	*copydst;
	char	*src_start;
	size_t	copydst_len;
	size_t	remaing;

	copydst = dest;
	src_start = (char *) src;
	remaing = size;
	while (remaing-- != 0 && *copydst != '\0')
		copydst++;
	copydst_len = copydst - dest;
	remaing = size - copydst_len;
	if (remaing == 0)
		return (copydst_len + ft_strlen((char *) src));
	while (*src != '\0')
	{
		if (remaing > 1)
		{
			*copydst++ = *src;
			remaing--;
		}
		src++;
	}
	*copydst = '\0';
	return (copydst_len + (src - src_start));
}

size_t	ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}