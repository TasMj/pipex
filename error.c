/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:11:35 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/12 19:57:35 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	err_msg(int n)
{
	if (n == 0)
		write(1, "pb env\n", 8);
	else if (n == 1)
		write(1, "Merci de bien rentrer 4 arguments\n", 34);
	else if (n == 2)
		write(1, "pb open file\n", 13);
	else if (n == 3)
		write(1, "pb pipe\n", 7);
	else if (n == 4)
		write(1, "pb child\n", 9);
	return (1);
}

int	err_msg_free(int n, t_pipex *pipex)
{
	if (n == 9)
		write(1, "pb cmd1\n", 8);
	else if (n == 10)
		write(1, "pb cmd2\n", 8);
	else if (n == 5)
		write(1, "pb path 1\n", 10);
	else if (n == 6)
		write(1, "pb path 2\n", 10);
	else if (n == 7)
		write(1, "pb argv cmd1\n", 13);
	else if (n == 8)
		write(1, "pb argv cmd2\n", 13);
	free_end(pipex);
	return (2);
}
