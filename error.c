/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:11:35 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/10 16:21:07 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int err_msg(int n)
{
    if (n == 1)
    {
		write(1, "Merci de bien rentrer 4 arguments\n", 34);
		return (1);
    }
    else if (n == 2)
    {
        write(1, "pb open file\n", 13);
        return (1);
    }
    else if (n == 3)
    {
        write(1, "pb pipe\n", 7);
        return (1);
    }
    return (0);
}