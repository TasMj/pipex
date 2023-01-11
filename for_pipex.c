/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:15:10 by tas               #+#    #+#             */
/*   Updated: 2023/01/11 14:49:21 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	try_acces(char *path, char *argv)
{
	char	*s;

	s = ft_strjoin_mod(path, "/", 0);
	s = ft_strjoin_mod(s, argv, 1);
	if (access(s, F_OK | X_OK) == 0)
	{
		free(s);
		return (0);
	}
	free(s);
	return (1);
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
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_with_points = env[i] + 5;
			path_split = ft_split(path_with_points, ':');
			while (path_split[j])
			{
				if (try_acces(path_split[j], argv) == 0)
				{
					path_without_points = ft_strjoin_mod(path_split[j], "/", 0);
					path_without_points = ft_strjoin_mod(path_without_points, argv, 1);
					free_tab(path_split);
					return (path_without_points);
				}
				j++;
			}
		}
		i++;
	}
	free_tab(path_split);
	return (NULL);
}

int	init_param_pipex(t_pipex *pipex, char **argv, char **__environ)
{
	pipex->path_cmd1 = find_path(__environ, get_arg(argv, 2));
	if (!pipex->path_cmd1)
		return (err_msg_free(5, pipex));
	pipex->path_cmd2 = find_path(__environ, get_arg(argv, 3));
	if (!pipex->path_cmd2)
		return (err_msg_free(6, pipex));
	pipex->argv_cmd1 = ft_split(get_arg(argv, 2), ' ');
	if (!pipex->argv_cmd1)
		return (err_msg_free(7, pipex));
	pipex->argv_cmd2 = ft_split(get_arg(argv, 3), ' ');
	if (!pipex->argv_cmd2)
		return (err_msg_free(8, pipex));
	return (0);
}

char	*get_arg(char **argv, int nb)
{
	int	i;

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
