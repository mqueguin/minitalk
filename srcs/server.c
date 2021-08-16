/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 12:20:10 by mqueguin          #+#    #+#             */
/*   Updated: 2021/08/16 19:14:57 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_buffer	buffer;

void	ft_init(void)
{
	buffer.count = 0;
	buffer.bit_count = 0;
	ft_memset(buffer.buff, 0, 1000);
}

void	ft_print(void)
{
	if (buffer.buff[buffer.count - 1] == '\0')
	{
		write(1, buffer.buff, ft_strlen(buffer.buff));
		write(1, "\n", 1);
		ft_init();
	}
	else if (buffer.count == 999)
	{
		write(1, buffer.buff, ft_strlen(buffer.buff));
		ft_init();
	}
}

void	store_bit(int bit)
{
	int	bit_max;

	bit_max = 128 >> buffer.bit_count;
	if (bit == 1)
		buffer.buff[buffer.count] = buffer.buff[buffer.count] | bit_max;
	buffer.bit_count++;
	if (buffer.bit_count == 8)
	{
		buffer.bit_count = 0;
		buffer.count++;
		ft_print();
	}	
}

void	ft_receive_bit(int sig, siginfo_t *si, void *arg)
{
	(void)arg;
	(void)si;
	if (sig != SIGUSR1 && sig != SIGUSR2)
	{
		printf("Error\n");
		exit(0);
	}
	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		if (sig == SIGUSR1)
			store_bit(0);
		else
			store_bit(1);
	}
}

int		main(void)
{
	struct	sigaction	sa;

	printf("The PID is : %d\n", getpid());
	ft_init();
	sa.sa_sigaction = &ft_receive_bit;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		usleep(100);
	return (0);
}
