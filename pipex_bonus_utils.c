/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evocatur <evocatur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:46:40 by evocatur          #+#    #+#             */
/*   Updated: 2023/07/26 16:24:29 by evocatur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_bonus(t_ppbx pipex, int status)
{
	char	*str;

	while (*pipex.cmd)
	{
		str = *pipex.cmd;
		free(str);
		pipex.cmd++;
	}
	free(pipex.cmd_path);
	if (status == EXIT_FAILURE)
		perror("Error");
	exit(status);
}
