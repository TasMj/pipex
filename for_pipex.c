/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:15:10 by tas               #+#    #+#             */
/*   Updated: 2023/01/08 17:44:16 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int     open_files(t_pipex *pipex, int argc, char **argv)
// {
// 	pipex->infile = open(argv[1], O_RDONLY);
// 	if (pipex->infile == -1)
// 		return (1);
// 	pipex->outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
// 	if (pipex->outfile == -1)
// 		return (1);
// 	return (0);
// }


char	*find_path(char **env)
{
	int		i;
	int		j;
	char	*path_with_points;
	char	*path_without_points;
	char	**path_stockage;

	i = 0;
	j = 1;
	while(env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
            path_with_points = malloc(sizeof(char) * ft_strlen(env[i] + 5) + 1);
			path_with_points = env[i] + 5;
			path_stockage = ft_split(path_with_points, ':');
			path_without_points = path_stockage[0];
			while (path_stockage[j])
			{
				path_without_points = ft_strjoin(path_without_points, path_stockage[j]);
                j++;	
			}
			path_without_points = ft_strjoin(path_without_points, "/");
			return (path_without_points);
		}
		i++;
	}
	return (NULL);
}

int	init_param_pipex(t_pipex *pipex, char **argv, char **__environ)
{
    (void)__environ;
	pipex->path = find_path(__environ);
    pipex->path_cmd1 = ft_strjoin(pipex->path, argv[2]);
	pipex->path_cmd2 = ft_strjoin(pipex->path, argv[3]);
	pipex->argv_cmd1 = ft_split(argv[2], ' ');
	pipex->argv_cmd2 = ft_split(argv[3], ' ');
    
    // printf("path: %s\n\n", pipex->path);
	// printf("cmd1: [%s]\n\n", pipex->path_cmd1);
	// printf("cmd2: [%s]\n\n", pipex->path_cmd2);
	return (0);
}

int	first_child(t_pipex *pipex, char **__environ)
{
	if (pipex->pid1 == 0)
	{
		dup2(pipex->pip[1], 1);
		close(pipex->pip[0]);
		dup2(pipex->infile, 0);
		execve(pipex->path_cmd1, pipex->argv_cmd1, __environ);
	}
	return (0);
}


int	second_child(t_pipex *pipex, char **__environ)
{
	if (pipex->pid2 == 0)
	{
		dup2(pipex->pip[0], 0);
		close(pipex->pip[1]);
		dup2(pipex->outfile, 1);
		execve(pipex->path_cmd2, pipex->argv_cmd2, __environ);
	}
	return (0);
}
