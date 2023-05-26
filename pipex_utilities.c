/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:26:02 by evocatur          #+#    #+#             */
/*   Updated: 2023/05/26 17:50:15 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex init_pipex(t_pipex pipex, char **argv)
{
	int		in_fd;
	int		out_fd;

	pipex.filein = argv[1];
	pipex.fileout = argv[4];
	pipex.cmd1 = ft_split(argv[2],' ');
	pipex.cmd2 = ft_split(argv[3],' ');
	in_fd = open(pipex.filein, O_WRONLY | O_CREAT, 0644);
	out_fd = open(pipex.fileout, O_WRONLY | O_CREAT, 0644);
	pipex.in_fd = in_fd;
	pipex.out_fd = out_fd;
	return (pipex);
}

void check_args(t_pipex pipex)
{
	if (access(pipex.filein, R_OK) == -1 || access(pipex.fileout, R_OK) == -1)
		exit_program(pipex);
	
	//more...
}

void exit_program(t_pipex pipex)
{
	free(pipex.cmd1);
	free(pipex.cmd2);
	close(pipex.in_fd);
	close(pipex.out_fd);
	unlink(pipex.filein);
	unlink(pipex.fileout);
}