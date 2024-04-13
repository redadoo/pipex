/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:46:40 by evocatur          #+#    #+#             */
/*   Updated: 2024/04/13 17:23:37 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_pipex(char **cmd, char *path)
{
	if (path != NULL)
		free(path);
	if (cmd != NULL)
		free_command(cmd);
}

void	exit_bonus(t_ppbx pipex, int status)
{
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
