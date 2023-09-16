/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:46:40 by evocatur          #+#    #+#             */
/*   Updated: 2023/09/14 15:21:37 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_pipex(char **cmd, char *path)
{
	int		i;
	char	*str;

	i = 0;
	if (path != NULL)
		free(path);
	while (cmd[i])
	{
		str = cmd[i];
		free(str);
		i++;
	}
}

void	exit_bonus(t_ppbx pipex, int status)
{
	char	*str;

	if (status > 1)
	{
		if (status == 2)
			write(2, "no such file or directory", 26);
		else if (status == 4)
			write(2, "not enough argument error", 26);
		else if (status == 5)
		{
			write(2, "command not found\n", 19);
			free_pipex(pipex.cmd, pipex.cmd_path);
			exit(EXIT_FAILURE);
		}
		else
			write(2, "File permession error", 22);
		write(1, "\n", 1);
		exit(EXIT_FAILURE);
	}
	else
	{
		free_pipex(pipex.cmd, pipex.cmd_path);
		exit(status);
	}
}

void	close_pipes(t_ppbx pipex)
{
	int	i;

	i = 0;
	while (i < 2 * (pipex.cmd_number - 1))
	{
		close(pipex.pipe[i]);
		i++;
	}
	free(pipex.pipe);
}

char	*acces_command(char *cmd_name, char **paths)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		if (cmd_path != NULL)
			free(cmd_path);
		cmd_path = ft_strjoin(paths[i], cmd_name);
		if (access(cmd_path, X_OK) == 0)
			break ;
		i++;
	}
	return (cmd_path);
}

char	*return_path(char *cmd, char **env)
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
	i = -1;
	return (cmd_path);
}
