/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:39:23 by jaehejun          #+#    #+#             */
/*   Updated: 2023/08/04 18:01:01 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	receive_acknowledgement(int signum);
void	send_pid(int server_pid, int client_pid);
void	send_message(int server_pid, char *message);
void	send_terminating_signal(int server_pid);

int	main(int argc, char *argv[])
{
	int		server_pid;
	int		client_pid;
	char	*message;

	if (argc != 3)
	{
		printf("Usage: ./client server_pid \"string_to_send\"\n");
		exit(1);
	}
	server_pid = atoi(argv[1]);
	message = argv[2];
	if (server_pid <= 100 || server_pid > 99999)
	{
		printf("server_pid is invalid\n");
		exit(1);
	}
	signal(SIGUSR1, receive_acknowledgement);
	client_pid = getpid();
	send_pid(server_pid, client_pid);
	send_message(server_pid, message);
	send_terminating_signal(server_pid);
	while (1)
		pause();
	return (0);
}

void	receive_acknowledgement(int signum)
{
	if (signum == SIGUSR1)
		printf("Received all messages!\n");
	exit(0);
}

void	send_pid(int server_pid, int client_pid)
{
	int	compare_bit;

	compare_bit = 1;
	while (compare_bit <= 65536)
	{
		if (client_pid & compare_bit)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		compare_bit = compare_bit << 1;
		usleep(150);
	}
}

void	send_message(int server_pid, char *message)
{
	int		message_index;
	int		compare_bit;

	message_index = 0;
	while (message[message_index] != '\0')
	{
		compare_bit = 1;
		while (compare_bit <= 128)
		{
			if (message[message_index] & compare_bit)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			compare_bit = compare_bit << 1;
			usleep(150);
		}
		message_index++;
	}
}

void	send_terminating_signal(int server_pid)
{
	int	compare_bit;
	int	terminating_character;

	compare_bit = 1;
	terminating_character = 0;
	while (compare_bit <= 128)
	{
		if (terminating_character & compare_bit)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		compare_bit = compare_bit << 1;
		usleep(150);
	}
}
