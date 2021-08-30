/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:31:57 by mqueguin          #+#    #+#             */
/*   Updated: 2021/08/30 13:05:54 by mqueguin         ###   ########.fr       */
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
		{
			if (kill(pid, SIGUSR2) != 0)
			{
				printf("Error\nUnable to send signal\n");
				exit(0);
			}
		}
		else
		{
			if (kill(pid, SIGUSR1) != 0)
			{
				printf("Error\nUnable to send signal\n");
				exit(0);
			}
		}
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
	if (!ft_check_pid(av[1]))
			return (-1);
	pid = ft_atoi(av[1]);
	i = -1;
	while (av[2][++i])
		send_bit(pid, av[2][i]);
	send_bit(pid, '\0');
	return (0);
}
