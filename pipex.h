/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:15:25 by user              #+#    #+#             */
/*   Updated: 2023/05/29 15:55:37 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "ft_libft/libft.h"

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	char	*filein;
	char	*fileout;
	char	**cmd1;
    char	**cmd2;
} t_pipex;

t_pipex	init_pipex(t_pipex pipex, char **argv);
void	check_args(t_pipex pipex);
void	exit_program(t_pipex pipex);
void	free_command(char **cmd);
void	execute_command(t_pipex pipex);
#endif