/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 12:20:10 by mqueguin          #+#    #+#             */
/*   Updated: 2021/08/17 16:40:23 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

t_buffer	g_buffer;

void	ft_init(void)
{
	ft_memset(g_buffer.buff, 0, 1000);
	g_buffer.count = 0;
	g_buffer.bit_count = 0;
}

void	ft_print(int pid_client)
{
	if (g_buffer.buff[g_buffer.count - 1] == '\0')
	{
		write(1, g_buffer.buff, ft_strlen(g_buffer.buff));
		write(1, "\n", 1);
		ft_init();
		kill(pid_client, SIGUSR1);
	}
}

void	store_bit(int bit, int pid_client)
{
	g_buffer.bit_max = 32768 >> g_buffer.bit_count;
	if (bit == 1)
		g_buffer.buff[g_buffer.count] = g_buffer.buff[g_buffer.count]
			| g_buffer.bit_max;
	g_buffer.bit_count++;
	if (g_buffer.bit_count == 16)
	{
		g_buffer.bit_count = 0;
		g_buffer.count++;
		if (g_buffer.count == 999)
		{
			write(1, g_buffer.buff, ft_strlen(g_buffer.buff));
			ft_init();
		}
		else
			ft_print(pid_client);
	}	
}

void	ft_receive_bit(int sig, siginfo_t *si, void *arg)
{
	(void)arg;
	if (sig != SIGUSR1 && sig != SIGUSR2)
	{
		printf("Error\n");
		exit(0);
	}
	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		if (sig == SIGUSR1)
			store_bit(0, si->si_pid);
		else
			store_bit(1, si->si_pid);
	}
}

int	main(void)
{
	struct sigaction	sa;

	printf("The PID is : %d\n", getpid());
	ft_init();
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &ft_receive_bit;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		usleep(100);
	return (0);
}
