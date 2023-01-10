/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:30:00 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/11 00:22:16 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_end(t_pipex *pipex)
{
	if (pipex->path_cmd1)
		free(pipex->path_cmd1);
	if (pipex->path_cmd2)
		free(pipex->path_cmd2);
	if (pipex->argv_cmd1)
		free_tab(pipex->argv_cmd1);
	if (pipex->argv_cmd2)
		free_tab(pipex->argv_cmd2);
}
