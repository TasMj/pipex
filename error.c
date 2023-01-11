/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:11:35 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/11 09:56:56 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	err_msg(int n)
{
	if (n == 1)
		write(1, "Merci de bien rentrer 4 arguments\n", 34);
	else if (n == 2)
		write(1, "pb open file\n", 13);
	else if (n == 3)
		write(1, "pb pipe\n", 7);
	else if (n == 4)
		write(1, "pb child\n", 9);
	return (1);
}

int err_msg_free(int n, t_pipex *pipex)
{
	if (n == 5)
	{
		free(pipex->path_cmd1);
		write(1, "pb path 1\n", 10);
	}
	else if (n == 6)
	{
		free(pipex->path_cmd1);	
		free(pipex->path_cmd2);	
		write(1, "pb path 2\n", 10);
	}
	else if (n == 7)
	{
		free(pipex->path_cmd1);	
		free(pipex->path_cmd2);
		free(pipex->argv_cmd1);
		write(1, "pb argv cmd1\n", 13);
	}
	else if (n == 8)
	{
		free(pipex->path_cmd1);	
		free(pipex->path_cmd2);
		free(pipex->argv_cmd1);
		free(pipex->argv_cmd2);
		write(1, "pb argv cmd2\n", 13);
	}
	return (2);
}