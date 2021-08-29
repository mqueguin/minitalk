/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:31:57 by mqueguin          #+#    #+#             */
/*   Updated: 2021/08/17 16:36:32 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

static	void	send_bit(int pid, unsigned char bit)
{
	int	i;

	i = -1;
	while (32768 >> ++i)
	{
		usleep(100);
		if ((32768 >> i) & bit)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
	}
}

void	ft_handler(int sig, siginfo_t *si, void *arg)
{
	(void)arg;
	(void)sig;
	(void)si;
	printf("The message has been received !\n");
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
		printf("Error\nExpected 2 arguments: pid and string\n");
		return (-1);
	}
	if (!ft_check_pid(pid))
		return (-1);
	pid = ft_atoi(av[1]);
	i = -1;
	while (av[2][++i])
		send_bit(pid, av[2][i]);
	send_bit(pid, '\0');
	pause();
	return (0);
}
