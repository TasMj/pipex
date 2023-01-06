/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:51:40 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/06 23:02:25 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **env)
{
	int i;

	i = 0;
	while(env[i])
	{
		if (env[i] == "PATH")
			return (env[i]);
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
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
	pipex.infile = open(argv[1], O_RDONLY, 00700);
	if (pipex.infile == -1)
		return (1);
	//OPEN fichier d'ecriture (sorite)
	pipex.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 00700);
	if (pipex.outfile == -1)
		return (1);
	//init pipe
	if (pipe(pipex.pip) == -1)
		return (1);


//2 //Recuperer les elt pour la fonction execve

	//env: trouver le path et le donner des 
	
	//cmd path
	
	//cmd
	pipex.cmd->cmd1 = argv[2];
	pipex.cmd->cmd2 = argv[3];
	
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
		execve(??????????, pipex.cmd->cmd1, ????????);
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
		execve(????????????, pipex.cmd->cmd2, ???????);
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
