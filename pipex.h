/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:50:58 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/07 18:00:03 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct s_cmd
{
    char *cmd1;
    char *cmd2;
}             t_cmd;

typedef struct s_pipex
{
    t_cmd   *cmd;
    int     infile;
    int     outfile;
    int     pip[2];
    int     pid1;
    int     pid2;
    char    *path;
    char    *path_cmd1;
    char    *path_cmd2;
}             t_pipex;



char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int     ft_strncmp(char *s1, char *s2, size_t n);
int     ft_strlen(char *str);



# endif
