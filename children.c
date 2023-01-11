/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:22:19 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/11 14:30:29 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_child(t_pipex *pipex, char **__environ)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		return (1);
	if (pipex->pid1 == 0)
	{
		dup2(pipex->infile_fd, 0);
		dup2(pipex->pip[1], 1);
		close_all(pipex);
		execve(pipex->path_cmd1, pipex->argv_cmd1, __environ);
	}
	return (0);
}

int	second_child(t_pipex *pipex, char **__environ)
{
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		return (1);
	if (pipex->pid2 == 0)
	{
		dup2(pipex->pip[0], 0);
		dup2(pipex->outfile_fd, 1);
		close_all(pipex);
		execve(pipex->path_cmd2, pipex->argv_cmd2, __environ);
	}
	return (0);
}
