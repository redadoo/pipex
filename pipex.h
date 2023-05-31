/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:15:25 by user              #+#    #+#             */
/*   Updated: 2023/05/31 14:14:44 by user             ###   ########.fr       */
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
	char	*cmd1_path;
	char	*cmd2_path;
} t_pipex;

t_pipex	init_pipex(t_pipex pipex, char **argv);
void	check_args(t_pipex pipex);
void	exit_program(t_pipex pipex);
void	free_command(char **cmd);
void	execute_command(t_pipex pipex);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlen(char *str);
#endif