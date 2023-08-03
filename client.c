/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:39:23 by jaehejun          #+#    #+#             */
/*   Updated: 2023/08/03 22:51:23 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	receive_acknowledgement(int signum);
void	send_pid(int server_pid, int client_pid);
void	send_message(int server_pid, char *message);

int	main(int argc, char *argv[])
{
	int		server_pid;
	int		client_pid;
	char	*message;

	if (argc != 3)
	{
		printf("Usage: ./client [server_pid] [string_to_send]\n");
		exit(1);
	}
	server_pid = atoi(argv[1]);
	message = argv[2];
	if (server_pid <= 100 || server_pid > 99999)
	{
		printf("server_pid is invalid\n");
		exit(1);
	}
	client_pid = getpid();
	if (client_pid <= 100 || client_pid > 99999)
	{
		printf("client_pid is invalid\n");
		exit(1);
	}
	printf("client_pid: %d\n", client_pid);
	signal(SIGUSR1, receive_acknowledgement);
	//send_pid(server_pid, client_pid);
	send_message(server_pid, message);
	return (0);
}

void	receive_acknowledgement(int signum)
{
	if (signum == SIGUSR1)
		printf("Received all messages!\n");
}

//void	send_pid(int server_pid, int client_pid)
//{
//	int	compare_bit;

//	compare_bit = 1;
//	while (compare_bit <= 65536)
//	{
//		if ((client_pid & compare_bit) == 1)
//		{
//			printf("1\n");
//			kill(server_pid, SIGUSR1);
//		}
//		else if ((client_pid & compare_bit) == 0)
//		{
//			printf("0\n");
//			kill(server_pid, SIGUSR2);
//		}
//		usleep(10000);
//		compare_bit = compare_bit << 1;
//	}
//}

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
			if ((message[message_index] & compare_bit) == 1)
				kill(server_pid, SIGUSR1);
			else if ((message[message_index] & compare_bit) == 0)
				kill(server_pid, SIGUSR2);
			sleep(1);
			compare_bit = compare_bit << 1;
		}
		message_index++;
	}
}