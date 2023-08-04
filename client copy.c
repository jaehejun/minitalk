/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:39:23 by jaehejun          #+#    #+#             */
/*   Updated: 2023/08/04 19:11:22 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

# define TRUE 1
# define FALSE 0

void	receive_acknowledgement(int signum);
void	send_pid(int server_pid, int client_pid);
void	send_message(int server_pid, char *message);
void	send_terminating_signal(int server_pid);

void	exit_program(char *error_message)
{
	printf("Error: %s\n", error_message);
	exit(1);
}

void	check_vaild_pid(int server_pid)
{
	if (server_pid <= 100 || server_pid > 99999)
		exit_program("server_pid is invalid");
}

int	main(int argc, char *argv[])
{
	int		server_pid;
	int		client_pid;
	char	*message;

	if (argc == 3)
	{
		server_pid = atoi(argv[1]);
		client_pid = getpid();
		message = argv[2];
		check_vaild_pid(server_pid);
		signal(SIGUSR1, receive_acknowledgement);
		send_pid(server_pid, client_pid);
		send_message(server_pid, message);
		send_terminating_signal(server_pid);
	}
	else
		exit_program("Usage: ./client server_pid \"string_to_send\"");
	return (0);
}

void	check_server_signal(int signum)
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
