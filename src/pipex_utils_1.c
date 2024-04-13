/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:15:48 by evocatur          #+#    #+#             */
/*   Updated: 2024/04/13 17:14:44 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_command(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(name)) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

int is_path(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '/')
			return 1;
		i++;
	}
	return 0;
}


char	*return_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*cmd_path;
	char	*tmp;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		cmd_path = paths[i];
		tmp = ft_strdup(paths[i]);
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, "/");
		free(tmp);
	}
	cmd_path = acces_command(cmd, paths);
	free_command(paths);
	return (cmd_path);
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
