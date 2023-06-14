/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:15:25 by user              #+#    #+#             */
/*   Updated: 2023/06/14 15:01:37 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H


# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

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

t_pipex	init_pipex(t_pipex pipex, char **argv, char **envp);
void	check_args(t_pipex pipex);
void	exit_program(t_pipex pipex);
void	free_command(char **cmd);
void	execute_command(t_pipex pipex);
int		ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	**ft_split(const char *s, char c);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlen_t(const char *str);
char	*ft_substr(char const *s, unsigned int start, unsigned int len);
void	*ft_calloc(size_t count, size_t size);
char	*get_next_line(int fd);
char	*ft_statstr(int fd, char *statstr);
char	*ft_strjoin(char *backup, char *buff);
char	*ft_strchr(const char *str, int ch);
char	*ft_backup(char *backup);
char	*ft_get_line(char *backup);
int		file_linecount(char *file);
char	*return_path(char *cmd, t_pipex pipex, char **envp);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
#endif