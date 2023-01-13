/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:30:00 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/13 17:06:41 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	free_all(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

void	free_end(t_pipex *pipex)
{
	if (pipex->cmd1)
		free(pipex->cmd1);
	if (pipex->cmd2)
		free(pipex->cmd2);
	if (pipex->path_cmd1)
		free(pipex->path_cmd1);
	if (pipex->path_cmd2)
		free(pipex->path_cmd2);
	if (pipex->argv_cmd1)
		free_tab(pipex->argv_cmd1);
	if (pipex->argv_cmd2)
		free_tab(pipex->argv_cmd2);
}

void	close_all(t_pipex *pipex)
{
	close(pipex->pip[0]);
	close(pipex->pip[1]);
	close(pipex->outfile_fd);
	close(pipex->infile_fd);
}
