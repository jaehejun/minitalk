/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:41:18 by jaehejun          #+#    #+#             */
/*   Updated: 2023/08/03 22:55:55 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//#define MAX_BIT 65536
void	receive_message(int signum);
void	receive_string(int signum);

int	main(void)
{
	signal(SIGUSR1, receive_string);
	signal(SIGUSR2, receive_string);
	printf("Server PID : %d\n", getpid());
	while (1)
		pause();
	return (0);
}

//void	receive_message(int signum)
//{
//	static int	compare_pid;
//	static int	client_pid;

//	if (compare_pid <= 65536)
//	{
//		if (compare_pid == 0)
//			compare_pid = 1;
//		if (signum == SIGUSR1)
//			client_pid = client_pid | compare_pid;
//		else if (signum == SIGUSR2)
//			client_pid = client_pid & compare_pid;
//		printf("compare_pid : %d\n", compare_pid);
//		compare_pid = compare_pid << 1;
//		printf("client_pid : %d\n", client_pid);
//	}
//	else if (compare_pid > 65536)
//	{
//		receive_string(signum, client_pid);
//	}
//}

void	receive_string(int signum)
{
	static int	compare_char;
	static int	received_character;
	if (compare_char <= 128)
	{
		if (compare_char == 0)
			compare_char = 1;
		if (signum == SIGUSR1)
			received_character = received_character | compare_char;
		else if (signum == SIGUSR2)
			received_character = received_character & compare_char;
		sleep(1);
		compare_char = compare_char << 1;
		printf("RECEIVED_1LOOP : %d\n", received_character);
		printf("COMPARE_CHAR : %d\n", compare_char);
	}
	else if (compare_char > 128)
	{
		if (received_character == 0)
		{
			//kill(client_pid, SIGUSR1);
			write(1, "1", 1);
		}
		else
		{
			printf("%c", received_character);
			compare_char = 0;
			received_character = 0;
		}
	}
}