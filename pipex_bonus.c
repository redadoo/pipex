/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:06:47 by evocatur          #+#    #+#             */
/*   Updated: 2023/07/30 16:31:02 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	creat_pipes(t_ppbx pipex)
{
	int	i;

	i = 0;
	while (i < pipex.cmd_number - 1)
	{
		if (pipe(pipex.pipe + 2 * i) < 0)
		{
			perror("nee");
			exit(0);
		}
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	int i;
	int mpipe[2 * (argc - 4)];
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
	pipex.pipe = (int *)malloc(sizeof(int) * pipex.cmd_number);
	if (!pipex.pipe)
		perror("ERR_PIPE");
	creat_pipes(pipex);
	pipex.cmd = ft_split(argv[i + 2], ' ');
	while (i < pipex.cmd_number)
 		exe_cmd_bonus(pipex, i++, argv, envp);		
	waitpid(-1, NULL, 0);
}
static void	sub_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

char	*return_path(char *cmd, char**env)
{
	int		i;
	char	**paths;
	char	*cmd_path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		cmd_path = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	cmd_path = acces_command(cmd, paths);
	return (cmd_path);
}

void	exe_cmd_bonus(t_ppbx p, int i, char **argv, char **envp)
{
	p.pid = fork();
	if (!p.pid)
	{
		if (i == 0)
			sub_dup2(p.in_fd, p.pipe[2 * i + 1]);
		else if (i == p.cmd_number - 1)
			sub_dup2(p.pipe[2 * i - 2], p.out_fd);
		else
			sub_dup2(p.pipe[2 * i - 2], p.pipe[2 * i + 1]);
		close_pipes(p);
		p.cmd = ft_split(argv[i + 2], ' ');
		p.cmd_path = return_path(p.cmd[0], envp);
		if (!p.cmd)
		{
			exit(1);
		}
		execve(p.cmd_path, p.cmd, envp);
	}
}
