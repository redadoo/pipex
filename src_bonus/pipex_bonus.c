/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:06:47 by evocatur          #+#    #+#             */
/*   Updated: 2023/09/14 13:17:24 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	check_error(t_ppbx pipex)
{
	if (pipex.in_fd == -1)
		exit_bonus(pipex, 2);
	if (access(pipex.filein, R_OK) == -1 || access(pipex.fileout, W_OK) == -1)
		exit_bonus(pipex, 3);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		status;
	t_ppbx	pipex;

	i = -1;
	if (argc < 5)
		exit_bonus(pipex, 4);
	pipex.filein = argv[1];
	pipex.fileout = argv[argc - 1];
	pipex.in_fd = open(pipex.filein, O_RDONLY);
	pipex.out_fd = open(pipex.fileout, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	pipex.cmd_number = argc - 3;
	check_error(pipex);
	pipex.cmd_path = NULL;
	pipex.cmd = NULL;
	pipex.pipe = (int *)malloc(sizeof(int) * 2 * (pipex.cmd_number - 1));
	if (!pipex.pipe)
		perror("ERR_PIPE");
	creat_pipes(pipex);
	while (++i < pipex.cmd_number)
		exe_cmd_bonus(pipex, i, argv, envp);
	close_pipes(pipex);
	waitpid(-1, &status, 0);
	return (0);
}

static void	sub_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

void	exe_cmd_bonus(t_ppbx p, int i, char **argv, char **envp)
{
	p.cmd = ft_split(argv[i + 2], ' ');
	p.cmd_path = return_path(p.cmd[0], envp);
	if (access(p.cmd_path, F_OK) == -1)
		exit_bonus(p, 5);
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
		if (!p.cmd)
			exit(1);
		execve(p.cmd_path, p.cmd, envp);
	}
}

void	creat_pipes(t_ppbx pipex)
{
	int	i;

	i = 0;
	while (i < pipex.cmd_number - 1)
	{
		if (pipe(pipex.pipe + 2 * i) < 0)
		{
			perror("PIPE ERR");
			exit(0);
		}
		i++;
	}
}
