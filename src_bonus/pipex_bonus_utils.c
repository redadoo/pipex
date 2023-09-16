/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:46:40 by evocatur          #+#    #+#             */
/*   Updated: 2023/09/16 13:10:20 by evocatur         ###   ########.fr       */
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
	if (cmd != NULL)
		free_command(cmd);
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
	pipex.pipe = NULL;
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
