/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edoardo <edoardo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:46:40 by evocatur          #+#    #+#             */
/*   Updated: 2023/07/30 16:00:32 by edoardo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_bonus(t_ppbx pipex, int status)
{
/* 	char	*str;

	while (*pipex.cmd)
	{
		str = *pipex.cmd;
		free(str);
		pipex.cmd++;
	}
	free(pipex.cmd_path); */
	if (status == EXIT_FAILURE)
		perror("Error");
	
	exit(status);
}

static size_t	lens(char *str, char div)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		if (*str != div)
		{
			++i;
			while (*str && *str != div)
				++str;
		}
		else
			++str;
	}
	return (i + 1);
}

char	**ft_split(const char *s, char c)
{
	char	**newstr;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	i = 0;
	newstr = (char **)ft_calloc(lens((char *)s, c), sizeof(char *));
	if (!newstr)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			j = 0;
			while (*s && *s != c && ++j)
				++s;
			newstr[i] = ft_substr(s - j, 0, j);
			i++;
		}
		else
			++s;
	}
	return (newstr);
}


int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((unsigned char)str1[i] == str2[i] && (i < n - 1)
		&& (unsigned char)str1[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
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

char	*ft_substr(char const *s, unsigned int start, unsigned int len)
{
	char			*newstr;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = start;
	if (!s || len < 0)
		return (NULL);
	while ((int)start < ft_strlen(s) && s[start] != '\0' && i < len)
	{
		start++;
		i++;
	}
	newstr = (char *)ft_calloc(i + 1, sizeof(char));
	if (!newstr)
		return (newstr);
	start = 0;
	while (start < i)
	{
		newstr[start] = s[j];
		start++;
		j++;
	}
	return (newstr);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*s;

	s = malloc(count * size);
	if (!s)
		return (NULL);
	i = 0;
	ft_bzero(s, size * count);
	return (s);
}

char	*ft_strjoin(char *backup, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!backup)
	{
		backup = (char *)malloc(1 * sizeof(char));
		backup[0] = '\0';
	}
	if (!backup || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(backup) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (backup)
		while (backup[++i] != '\0')
			str[i] = backup[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(backup) + ft_strlen(buff)] = '\0';
	free(backup);
	return (str);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = NULL;
	p = (unsigned char *)b;
	while (len--)
	{
		*p++ = (unsigned char)c;
	}
	return (b);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlen_t(const char *str)
{
	int	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_backup(char *backup)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(backup) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (backup[i])
		str[j++] = backup[i++];
	str[j] = '\0';
	free(backup);
	return (str);
}

char	*ft_get_line(char *backup)
{
	int		i;
	char	*str;

	i = 0;
	if (!backup[i])
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (backup[i] && backup[i] != '\n')
	{
		str[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
	{
		str[i] = backup[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}


char	*ft_statstr(int fd, char *statstr)
{
	char	*str;
	int		bytes;

	str = (char *)malloc(BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(statstr, '\n') && bytes != 0)
	{
		bytes = read(fd, str, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(str);
			return (NULL);
		}
		str[bytes] = '\0';
		statstr = ft_strjoin(statstr, str);
	}
	free(str);
	return (statstr);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*statstr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	statstr = ft_statstr(fd, statstr);
	if (!statstr)
		return (NULL);
	str = ft_get_line(statstr);
	statstr = ft_backup(statstr);
	return (str);
}

void	close_pipes(t_ppbx pipex)
{
	int	i;

	i = 0;
	while (i < (pipex.cmd_number))
	{
		close(pipex.pipe[i]);
		i++;
	}
}