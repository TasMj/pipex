/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:15:10 by tas               #+#    #+#             */
/*   Updated: 2023/01/10 14:24:15 by tmejri           ###   ########.fr       */
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

int	try_acces(char *path, char *argv)
{
	char *s;
	
	s = ft_strjoin(path, "/");
	s = ft_strjoin(s, argv);
	if (access(s, F_OK | X_OK) == 0)
	{
		free(s);	
		return (0);
	}
	free(s);	
	return(1);
}

char	*find_path(char **env, char *argv)
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
				if (try_acces(path_stockage[j], argv) == 0)
				{
					path_without_points = ft_strjoin(path_stockage[j], "/");
					path_without_points = ft_strjoin(path_without_points, argv);
					return (path_without_points);
				}
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

char *get_arg(char **argv, int nb)
{
	int i;

	i = 0;
	if (argv[nb][i] != '/')
		return (argv[nb]);
	else
	{
		i++;
		while (argv[nb][i] != '/')
			i++;
	}
	return (argv[nb] + i + 1);
}

int	init_param_pipex(t_pipex *pipex, char **argv, char **__environ)
{
    pipex->path_cmd1 = find_path(__environ, get_arg(argv, 2));
	pipex->path_cmd2 = find_path(__environ, get_arg(argv, 3));
	pipex->argv_cmd1 = ft_split(get_arg(argv, 2), ' ');
	pipex->argv_cmd2 = ft_split(get_arg(argv, 3), ' ');
    
	printf("cmd1: [%s]\n\n", pipex->path_cmd1);
	printf("cmd2: [%s]\n\n", pipex->path_cmd2);
	return (0);
}

int	first_child(t_pipex *pipex, char **__environ)
{

	if (pipex->pid1 == 0)
	{
		dup2(pipex->infile_fd, 0);
		dup2(pipex->pip[1], 1);
		close(pipex->pip[0]);
		close(pipex->pip[1]);
		close(pipex->infile_fd);
		close(pipex->outfile_fd);
		// printf("cmd1: [%s]\n\n", pipex->path_cmd1);
		// printf("cmd2: [%s]\n\n", pipex->path_cmd2);

		execve(pipex->path_cmd1, pipex->argv_cmd1, __environ);
		
	}
	return (0);
}


int	second_child(t_pipex *pipex, char **__environ)
{
	pipex->pid1 = fork();
	if (pipex->pid2 < 0)
		return (1);
	if (pipex->pid2 == 0)
	{
		dup2(pipex->pip[0], 0);
		dup2(pipex->outfile_fd, 1);
		close(pipex->pip[0]);
		close(pipex->pip[1]);
		close(pipex->outfile_fd);
		close(pipex->infile_fd);
		execve(pipex->path_cmd2, pipex->argv_cmd2, __environ);
	}
	return (0);
}
