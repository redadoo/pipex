/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 09:49:10 by edoardo           #+#    #+#             */
/*   Updated: 2023/10/26 16:58:47 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>

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

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		pipe[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*filein;
	char	*fileout;
	char	**cmd1;
	char	**cmd2;
	char	*cmd1_path;
	char	*cmd2_path;
	int		status;
}	t_pipex;

char	*return_path(char *cmd, char**env);
void	exe_cmd_bonus(t_ppbx pipex, int i, char**argv, char **envp);
void	exit_bonus(t_ppbx pipex, int status);
char	*ft_strdup(const char *s);
char	**ft_split(const char *s, char c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*acces_command(char *cmd_name, char **paths);
char	*ft_substr(char const *s, unsigned int start, unsigned int len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char *backup, char *buff);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
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
void	free_pipex(char **cmd, char *path);

t_pipex	*init_pipex(char **argv, char **envp);
void	check_args(t_pipex *p);
void	exit_program(t_pipex *p, int status);
void	execute_command(t_pipex *p, char **env);
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
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	first_child(t_pipex *p, char **env);
void	second_child(t_pipex *p, char **env);
char	*acces_command(char *cmd_name, char **paths);
char	*my_getenv(char *name, char **env);
void	free_command(char **tab);
int		is_path(char *str);
#endif