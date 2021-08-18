/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:31:57 by mqueguin          #+#    #+#             */
/*   Updated: 2021/08/17 16:35:49 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static	void	send_bit(int pid, unsigned char bit)
{
	int	i;

	i = -1;
	while (128 >> ++i)
	{
		usleep(100);
		if ((128 >> i) & bit)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
	}
}

int	main(int ac, char **av)
{
	int					pid;
	int					i;

	if (ac != 3)
	{
		printf("Error\nExpected 2 arguments: pid and string\n");
		return (-1);
	}
	pid = ft_atoi(av[1]);
	i = -1;
	while (av[2][++i])
		send_bit(pid, av[2][i]);
	send_bit(pid, '\0');
	return (0);
}
