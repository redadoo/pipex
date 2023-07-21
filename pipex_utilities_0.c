/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilities_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:03:51 by evocatur          #+#    #+#             */
/*   Updated: 2023/07/22 01:27:35 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex init_pipex(t_pipex pipex, char **argv, char **envp)
{
	pipex.filein = argv[1];
	pipex.fileout = argv[4];
	pipex.cmd1 = ft_split(argv[2],' ');
	pipex.cmd2 = ft_split(argv[3],' ');
	pipex.in_fd = open(pipex.filein, O_RDONLY);
	pipex.out_fd = open(pipex.fileout, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	pipex.cmd1_path = return_path(pipex.cmd1[0], pipex, envp);
	pipex.cmd2_path = return_path(pipex.cmd2[0], pipex, envp);
	return (pipex);
}

void    check_args(t_pipex pipex)
{
/* 	if (access(pipex.filein, R_OK) == -1 || access(pipex.fileout, W_OK) == -1)
	{
		exit_program(pipex, EXIT_FAILURE);
	} */
}

void    exit_program(t_pipex pipex,int status)
{
	free_command(pipex.cmd1);
	free_command(pipex.cmd2);
	free(pipex.cmd1);
	free(pipex.cmd2);
	free(pipex.cmd1_path);
	free(pipex.cmd2_path);
	//unlink(pipex.fileout);
	//unlink(pipex.filein);
	if (status == EXIT_FAILURE)
		perror("Error");
	exit(status);
}

void    free_command(char **cmd)
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

char    *return_path(char *cmd, t_pipex pipex, char**env)
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
		i++;
	}
	cmd_path = acces_command(cmd,paths);
	return (cmd_path);
}