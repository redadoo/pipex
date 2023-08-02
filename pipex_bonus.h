/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 09:49:10 by edoardo           #+#    #+#             */
/*   Updated: 2023/08/02 15:10:30 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_ppbx
{
	int		in_fd;
	int		out_fd;
	int		cmd_number;
	pid_t	pid;
	int		*pipe;
	char	*filein;
	char	*fileout;
	char	**cmd;
	char	*cmd_path;
}	t_ppbx;

void	exe_cmd_bonus(t_ppbx pipex, int i, char**argv, char **envp);
char	*return_path(char *cmd, char**env);
void	exit_bonus(t_ppbx pipex, int status);
char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*acces_command(char *cmd_name, char **paths);
char	*ft_substr(char const *s, unsigned int start, unsigned int len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char *backup, char *buff);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
int		ft_strlen(const char *s);
char	*ft_get_line(char *backup);
char	*get_next_line(int fd);
char	*ft_get_line(char *backup);
char	*ft_backup(char *backup);
char	*ft_strchr(const char *s, int c);
char	*ft_statstr(int fd, char *statstr);
void	close_pipes(t_ppbx pipex);
void	creat_pipes(t_ppbx pipex);

#endif