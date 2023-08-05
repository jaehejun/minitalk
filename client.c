/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:39:23 by jaehejun          #+#    #+#             */
/*   Updated: 2023/08/05 19:45:32 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char *argv[])
{
	int		server_pid;
	int		client_pid;
	char	*message;

	if (argc != 3)
	{
		write(1, "Usage: ./client server_pid \"string_to_send\"\n", 45);
		exit(1);
	}
	server_pid = ft_atoi(argv[1]);
	client_pid = getpid();
	message = argv[2];
	if (server_pid <= 100 || server_pid > 99998)
	{
		write(1, "server_pid is invalid\n", 22);
		exit(1);
	}
	signal(SIGUSR1, receive_server_signal);
	send_pid(server_pid, client_pid);
	send_message(server_pid, message);
	send_terminating_signal(server_pid);
	while (1)
		pause();
	return (0);
}

void	receive_server_signal(int signum)
{
	if (signum == SIGUSR1)
		write(1, "Received all messages!\n", 23);
	exit(0);
}

void	send_pid(int server_pid, int client_pid)
{
	int	compare_bit;
	int	check_signal;

	compare_bit = 1;
	while (compare_bit <= 65536)
	{
		if (client_pid & compare_bit)
		{
			check_signal = kill(server_pid, SIGUSR1);
			check_sending_signal(check_signal);
		}
		else
		{
			check_signal = kill(server_pid, SIGUSR2);
			check_sending_signal(check_signal);
		}
		compare_bit = compare_bit << 1;
		usleep(200);
	}
}

void	send_message(int server_pid, char *message)
{
	int		message_index;
	int		compare_bit;
	int		check_signal;

	message_index = 0;
	while (message[message_index] != '\0')
	{
		compare_bit = 1;
		while (compare_bit <= 128)
		{
			if (message[message_index] & compare_bit)
			{
				check_signal = kill(server_pid, SIGUSR1);
				check_sending_signal(check_signal);
			}
			else
			{
				check_signal = kill(server_pid, SIGUSR2);
				check_sending_signal(check_signal);
			}
			compare_bit = compare_bit << 1;
			usleep(200);
		}
		message_index++;
	}
}

void	send_terminating_signal(int server_pid)
{
	int	compare_bit;
	int	terminating_character;
	int	check_signal;

	compare_bit = 1;
	terminating_character = 0;
	while (compare_bit <= 128)
	{
		if (terminating_character & compare_bit)
		{
			check_signal = kill(server_pid, SIGUSR1);
			check_sending_signal(check_signal);
		}
		else
		{
			check_signal = kill(server_pid, SIGUSR2);
			check_sending_signal(check_signal);
		}
		compare_bit = compare_bit << 1;
		usleep(200);
	}
}
