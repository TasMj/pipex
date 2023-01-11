/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:15:10 by tas               #+#    #+#             */
/*   Updated: 2023/01/11 17:46:57 by tas              ###   ########.fr       */
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

char	*find_path(char **env, char *argv, t_path p)
{
	p.i = 0;
	p.j = 0;
	while (env[p.i])
	{
		if (ft_strncmp(env[p.i], "PATH=", 5) == 0)
		{
			p.path_with_points = env[p.i] + 5;
			p.path_split = ft_split(p.path_with_points, ':');
			while (p.path_split[p.j])
			{
				if (try_acces(p.path_split[p.j], argv) == 0)
				{
					p.path_without = ft_strjoin_mod(p.path_split[p.j], "/", 0);
					p.path_without = ft_strjoin_mod(p.path_without, argv, 1);
					free_tab(p.path_split);
					return (p.path_without);
				}
				p.j++;
			}
		}
		p.i++;
	}
	free_tab(p.path_split);
	return (NULL);
}

int	init_param(t_pipex *pipex, char **argv, char **__environ, t_path p)
{
	pipex->path_cmd1 = find_path(__environ, get_arg(argv, 2), p);
	if (!pipex->path_cmd1)
		return (err_msg_free(5, pipex));
	pipex->path_cmd2 = find_path(__environ, get_arg(argv, 3), p);
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
