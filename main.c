/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:51:40 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/10 16:45:22 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **__environ)
{
	t_pipex	pipex;

	if (argc != 5)
		return (err_msg(1)); // return pour sortir
	pipex.infile_fd = open(argv[1], O_RDONLY);
	if (pipex.infile_fd == -1)
		return (err_msg(2));
	pipex.outfile_fd = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.outfile_fd == -1)
		return (err_msg(2));
	if (pipe(pipex.pip) == -1)
		return (err_msg(3));
	init_param_pipex(&pipex, argv, __environ);
	first_child(&pipex, __environ);
	second_child(&pipex, __environ);
	close(pipex.pip[0]);
	close(pipex.pip[1]);
	close(pipex.outfile_fd);
	close(pipex.infile_fd);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	

	

	return (0);
}
