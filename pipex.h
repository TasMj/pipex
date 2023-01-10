/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:50:58 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/10 16:38:39 by tmejri           ###   ########.fr       */
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
    int     infile_fd;
    int     outfile_fd;
    int     pip[2];
    pid_t     pid1;
    pid_t     pid2;
    char    *path;
    char    *path_cmd1;
    char    *path_cmd2;
    char    **argv_cmd1;
    char    **argv_cmd2;



    
}             t_pipex;



char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int     ft_strncmp(char *s1, char *s2, size_t n);
int     ft_strlen(char *str);
char	*find_path(char **env, char *argv);
int     open_files(t_pipex *pipex, int argc, char **argv);
int     init_param_pipex(t_pipex *pipex, char **argv, char **__environ);
int     first_child(t_pipex *pipex, char **__environ);
int     second_child(t_pipex *pipex, char **__environ);
int     try_acces(char *path, char *argv);
int     err_msg(int n);
void    free_tab(char **tab);
char    *get_arg(char **argv, int nb);












# endif
