/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:51:40 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/07 18:00:41 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **env)
{
	int		i;
	int		j;
	char	*path_with_points;
	char	*path_without_points;
	char	**path_stockage;

	i = 0;
	j = 1;
	path_without_points = NULL;
	while(env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_with_points = ft_strjoin("", env[i] + 5);
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


int	main(int argc, char **argv, char **__environ)
{
// 0 //Verif parametres

	if (argc != 5)
	{
		write(1, "Merci de bien rentrer 4 arguments\n", 34);
		return (1);
	}

//1	//OPEN fichier
	
	t_pipex	pipex;
	

	//OPEN fichier de lecture (entrée)
	pipex.infile = open(argv[1], O_RDONLY, 00777);
	if (pipex.infile == -1)
		return (1);
	//OPEN fichier d'ecriture (sorite)
	pipex.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 00777);
	if (pipex.outfile == -1)
		return (1);
	//init pipe
	if (pipe(pipex.pip) == -1)
		return (1);


//2 //Recuperer les elt pour la fonction execve

	//path
	pipex.path = find_path(__environ);

	//cmd
	pipex.cmd->cmd1 = argv[2];
	pipex.cmd->cmd2 = argv[3];
	pipex.path_cmd1 = ft_strjoin(pipex.path, pipex.cmd->cmd1);
	pipex.path_cmd2 = ft_strjoin(pipex.path, pipex.cmd->cmd2);
	
	char ** c1 = &pipex.path_cmd1;
	char ** c2 = &pipex.path_cmd2;
	
//3 //GENERER LES ENFANTS 

	//generer l'enfant 1
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		return (1);
	if (pipex.pid1 == 0)
	{
		dup2(pipex.pip[1], 1);
		close(pipex.pip[0]);
		dup2(pipex.infile, 0);
		execve(pipex.path_cmd1, c1, __environ);
	}
	
	//generer l'enfant 2
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		return (1);
	if (pipex.pid2 == 0)
	{
		dup2(pipex.pip[0], 0);
		close(pipex.pip[1]);
		dup2(pipex.outfile, 1);
		execve(pipex.path_cmd2, c2, __environ);
	}

//5 //FIN PROGRAMME
	close(pipex.pip[0]);
	close(pipex.pip[1]);

//4 //attendre les enfant

	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);

	//free


	return (0);
}
