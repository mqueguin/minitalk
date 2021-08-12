/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 12:20:10 by mqueguin          #+#    #+#             */
/*   Updated: 2021/08/12 14:52:55 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	ft_receive_bit(int sig, siginfo_t *si, void *arg)
{
	(void)arg;
	(void)si;
	if (sig != SIGUSR1 && sig != SIGUSR2)
	{
		printf("Error\n");
		exit(0);
	}
	else if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		if (sig == SIGUSR1)
			printf("Le signal est sigusr1\n");
		else
			printf("Le signal est sigusr2\n");
	}
}

int		main(void)
{
	struct	sigaction	sa;

	sa.sa_sigaction = &ft_receive_bit;
	printf("The PID is : %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		;
	return (0);
}
