/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:31:57 by mqueguin          #+#    #+#             */
/*   Updated: 2021/08/16 16:51:25 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	send_bit(int pid, unsigned char bit)
{
	int bit_max;

	bit_max = 128;
	while (bit_max)
	{
		usleep(100);
		if (bit_max & bit)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		bit_max = bit_max >> 1;
	}
}

void	ft_handler(int sig, siginfo_t *si, void *arg)
{
	(void)arg;
	(void)sig;
	(void)si;
	printf("Error enfin je pense\n");
	exit(-1);
}

int		main(int ac, char **av)
{
	struct	sigaction	sa;
	int					pid;
	int					i;

	sa.sa_sigaction = ft_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	if (ac != 3)
	{
		printf("Error\nExpected 2 arguments: pid and string\n");
		return (-1);
	}

	/** Ici faire fonction pour envoyer sigusr1 ou sigusr2 **/
	pid = ft_atoi(av[1]);
	i = -1;
	while (av[2][++i])
		send_bit(pid, av[2][i]);
	send_bit(pid, '\0'); //Envoie du \0 pour signifier la fin de la chaine
	return (0);
}
