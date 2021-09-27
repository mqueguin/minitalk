/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:31:57 by mqueguin          #+#    #+#             */
/*   Updated: 2021/09/27 12:31:40 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static	void	send_bit(int pid, unsigned char bit)
{
	int	i;

	i = -1;
	while (32768 >> ++i)
	{
		usleep(100);
		if ((32768 >> i) & bit)
		{
			if (kill(pid, SIGUSR2) != 0)
			{
				write(2, "Error\nUnable to send signal\n", 28);
				exit(0);
			}
		}
		else
		{
			if (kill(pid, SIGUSR1) != 0)
			{
				write(2, "Error\nUnable to send signal\n", 43);
				exit(0);
			}
		}
	}
}

void	ft_handler(int sig, siginfo_t *si, void *arg)
{
	(void)arg;
	(void)sig;
	(void)si;
	write(1, "The message has been received !\n", 32);
	exit(0);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					pid;
	int					i;

	sa.sa_sigaction = ft_handler;
	sigaction(SIGUSR1, &sa, NULL);
	if (ac != 3)
	{
		write(2, "Error\nExpected 2 arguments: pid and string\n", 43);
		return (-1);
	}
	if (!ft_check_pid(av[1]))
		return (-1);
	pid = ft_atoi(av[1]);
	i = -1;
	while (av[2][++i])
		send_bit(pid, av[2][i]);
	send_bit(pid, '\0');
	pause();
	return (0);
}
