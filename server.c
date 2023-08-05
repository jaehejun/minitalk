/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:41:18 by jaehejun          #+#    #+#             */
/*   Updated: 2023/08/05 19:44:27 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(void)
{
	signal(SIGUSR1, receive_signal);
	signal(SIGUSR2, receive_signal);
	write(1, "Server PID : ", 13);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}

void	receive_signal(int signum)
{
	static int	bit_pid;
	static int	c_pid;

	if (bit_pid <= 65536)
	{
		if (bit_pid == 0)
			bit_pid = 1;
		if (signum == SIGUSR1)
			c_pid = c_pid | bit_pid;
		bit_pid = bit_pid << 1;
		usleep(50);
	}
	else
		receive_string(signum, &c_pid, &bit_pid);
}

void	receive_string(int signum, int *c_pid, int *bit_pid)
{
	static int	bit_char;
	static int	one_char;

	if (bit_char <= 128)
	{
		if (bit_char == 0)
			bit_char = 1;
		if (signum == SIGUSR1)
			one_char = one_char | bit_char;
		bit_char = bit_char << 1;
		usleep(30);
	}
	if (bit_char > 128)
		print_character(c_pid, bit_pid, &bit_char, &one_char);
}

void	print_character(int *c_pid, int *bit_pid, int *bit_char, int *one_char)
{
	int	check_signal;

	if (*one_char == 0)
	{
		check_signal = kill(*c_pid, SIGUSR1);
		check_sending_signal(check_signal);
		write(1, "\n", 1);
		*bit_char = 0;
		*one_char = 0;
		*bit_pid = 0;
		*c_pid = 0;
	}
	else
	{
		write(1, one_char, 1);
		*bit_char = 0;
		*one_char = 0;
		usleep(30);
	}
}
