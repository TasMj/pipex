/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 18:15:10 by tas               #+#    #+#             */
/*   Updated: 2023/01/13 18:13:13 by tmejri           ###   ########.fr       */
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

char	*get_command(char *argv)
{
	int		i;
	int		j;
	char	*cmd;

	i = 0;
	while (argv[i] && argv[i] != ' ')
		i++;
	j = 0;
	cmd = malloc(sizeof(char) * i + 1);
	if (!cmd)
		return (NULL);
	while (j <= i)
	{
		cmd[j] = argv[j];
		j++;
	}
	j--;
	cmd[j] = '\0';
	return (cmd);
}

char	*find_path(char **env, char *argv, t_path p)
{
	p.i = 0;
	p.j = 0;
	while (env[p.i] && argv)
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
	pipex->cmd1 = get_command(argv[2] + extract_str(argv[2]));
	if (!pipex->cmd1)
		return (err_msg_free(9, pipex));
	pipex->cmd2 = get_command(argv[3] + extract_str(argv[3]));
	if (!pipex->cmd2)
		return (err_msg_free(10, pipex));
	pipex->path_cmd1 = find_path(__environ, get_arg(pipex->cmd1), p);
	if (!pipex->path_cmd1)
		return (err_msg_free(5, pipex));
	pipex->path_cmd2 = find_path(__environ, get_arg(pipex->cmd2), p);
	if (!pipex->path_cmd2)
		return (err_msg_free(6, pipex));
	pipex->argv_cmd1 = ft_split(get_arg(argv[2]), ' ');
	if (!pipex->argv_cmd1)
		return (err_msg_free(7, pipex));
	pipex->argv_cmd2 = ft_split(get_arg(argv[3]), ' ');
	if (!pipex->argv_cmd2)
		return (err_msg_free(8, pipex));
	return (0);
}

char	*get_arg(char *argv)
{
	int	i;

	i = 0;
	if (argv[i] != '/')
		return (argv);
	else
	{
		i++;
		if (argv[i] != 'b')
			return (NULL);
		i++;
		if (argv[i] != 'i')
			return (NULL);
		i++;
		if (argv[i] != 'n')
			return (NULL);
		i++;
		if (argv[i] != '/')
			return (NULL);
		i++;
	}
	return (argv + i);
}
