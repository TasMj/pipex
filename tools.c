/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 11:28:38 by tas               #+#    #+#             */
/*   Updated: 2023/01/11 14:05:25 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_mod(char *s1, char *s2, int mode)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s1 || !s2)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	if (mode == 1)
		free(s1);
	else if (mode == 2)
		free(s2);
	else if (mode == 3)
		free_all(s1, s2);
	return (dest);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	char	*ss1;
	char	*ss2;
	size_t	i;

	ss1 = s1;
	ss2 = s2;
	i = 0;
	while (i < n)
	{
		if (ss1[i] == ss2[i])
			i++;
		else
			return ((unsigned char)ss1[i] - (unsigned char)ss2[i]);
	}
	return (0);
}
