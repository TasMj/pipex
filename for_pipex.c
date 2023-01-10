/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:15:10 by tas               #+#    #+#             */
/*   Updated: 2023/01/10 16:55:05 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	char	**path_split;

	i = 0;
	j = 1;
	while(env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
            path_with_points = malloc(sizeof(char) * ft_strlen(env[i] + 5) + 1);
			path_with_points = env[i] + 5;
			path_split = ft_split(path_with_points, ':');
			path_without_points = path_split[0];
			while (path_split[j])
			{
				if (try_acces(path_split[j], argv) == 0)
				{
					path_without_points = ft_strjoin(path_split[j], "/");
					path_without_points = ft_strjoin(path_without_points, argv);
					free_tab(path_split);	
					return (path_without_points);
				}
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

int	init_param_pipex(t_pipex *pipex, char **argv, char **__environ)
{
    pipex->path_cmd1 = find_path(__environ, get_arg(argv, 2));
	pipex->path_cmd2 = find_path(__environ, get_arg(argv, 3));
	pipex->argv_cmd1 = ft_split(get_arg(argv, 2), ' ');
	pipex->argv_cmd2 = ft_split(get_arg(argv, 3), ' ');
	return (0);
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



int	first_child(t_pipex *pipex, char **__environ)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		return (1);
	if (pipex->pid1 == 0)
	{
		dup2(pipex->infile_fd, 0);
		dup2(pipex->pip[1], 1);
		close(pipex->pip[0]);
		close(pipex->pip[1]);
		close(pipex->infile_fd);
		close(pipex->outfile_fd);
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
		close(pipex->pip[0]);
		close(pipex->pip[1]);
		close(pipex->outfile_fd);
		close(pipex->infile_fd);
		execve(pipex->path_cmd2, pipex->argv_cmd2, __environ);
	}
	return (0);
}
