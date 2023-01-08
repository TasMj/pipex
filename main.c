/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:51:40 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/08 17:43:48 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **__environ)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		write(1, "Merci de bien rentrer 4 arguments\n", 34);
		return (1);
	}
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile == -1)
		return (1);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.outfile == -1)
		return (1);
	if (pipe(pipex.pip) == -1)
		return (1);
	init_param_pipex(&pipex, argv, __environ);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(&pipex, __environ);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(&pipex, __environ);
	close(pipex.pip[0]);
	close(pipex.pip[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	//free

	return (0);
}
