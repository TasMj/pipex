/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:21:34 by tas               #+#    #+#             */
/*   Updated: 2023/01/10 23:18:27 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	nb_word(const char *s, char c)
{
	size_t	n;
	size_t	i;
	size_t	compteur;

	n = 1;
	i = 0;
	compteur = 0;
	while (s[i])
	{
		if (s[i] == c)
			n = 1;
		if (s[i] != c && n == 1)
		{
			compteur++;
			n = 0;
		}
		i++;
	}
	return (compteur);
}

static char	*ft_copy(char *dest, char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**s_split;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	s_split = (char **)malloc(sizeof(char *) * (nb_word(s, c) + 1));
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			k = 0;
			while (s[i + k] != c && s[i + k] != '\0')
				k++;
			s_split[j] = (char *)malloc(sizeof(char) * (k + 1));
			ft_copy(s_split[j], s + i, c);
			i += k;
			j++;
		}
	}
	s_split[j] = NULL;
	return (s_split);
}
