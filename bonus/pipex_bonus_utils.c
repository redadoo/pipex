/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:46:40 by evocatur          #+#    #+#             */
/*   Updated: 2023/08/21 11:49:09 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	free_pipex(t_ppbx pipex)
{
	char	*str;

	while (*pipex.cmd)
	{
		str = *pipex.cmd;
		free(str);
		pipex.cmd++;
	}
	free(pipex.cmd_path);
}

void	exit_bonus(t_ppbx pipex, int status)
{
	char	*str;

	if (status > 1)
	{
		if (status == 2)
			perror("input file not found Error");
		else if (status == 4)
			perror("not enough argument error");
		else
			perror("File permession error");
		exit(EXIT_FAILURE);
	}
	free_pipex(pipex);
	if (status == EXIT_FAILURE)
		perror("Error");
	else if (status == 2)
	{
		perror("Error");
		exit(0);
	}
	exit(status);
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

	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd_name);
		if (access(cmd_path, X_OK) == 0)
			break ;
		i++;
	}
	return (cmd_path);
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
