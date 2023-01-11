/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:51:40 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/11 17:46:39 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **__environ)
{
	t_pipex	pipex;
	t_path	p;

	if (!__environ)
		return (err_msg(0));
	if (argc != 5)
		return (err_msg(1));
	pipex.infile_fd = open(argv[1], O_RDONLY);
	if (pipex.infile_fd == -1)
		return (err_msg(2));
	pipex.outfile_fd = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.outfile_fd == -1)
		return (err_msg(2));
	if (pipe(pipex.pip) == -1)
		return (err_msg(3));
	if (init_param(&pipex, argv, __environ, p) == 2)
		return (1);
	first_child(&pipex, __environ);
	second_child(&pipex, __environ);
	close_all(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	free_end(&pipex);
	return (0);
}
