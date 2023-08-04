/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:41:18 by jaehejun          #+#    #+#             */
/*   Updated: 2023/08/04 18:01:34 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	receive_message(int signum);
void	receive_string(int signum, int *client_pid, int *compare_pid);

int	main(void)
{
	signal(SIGUSR1, receive_message);
	signal(SIGUSR2, receive_message);
	printf("Server PID : %d\n", getpid());
	while (1)
		pause();
	return (0);
}

void	receive_message(int signum)
{
	static int	compare_pid;
	static int	client_pid;

	if (compare_pid <= 65536)
	{
		if (compare_pid == 0)
			compare_pid = 1;
		if (signum == SIGUSR1)
			client_pid = client_pid | compare_pid;
		compare_pid = compare_pid << 1;
		usleep(100);
	}
	else
		receive_string(signum, &client_pid, &compare_pid);
}

void	receive_string(int signum, int *client_pid, int *compare_pid)
{
	static int	compare_char;
	static int	received_character;

	if (compare_char <= 128)
	{
		if (compare_char == 0)
			compare_char = 1;
		if (signum == SIGUSR1)
			received_character = received_character | compare_char;
		compare_char = compare_char << 1;
		usleep(100);
	}
	if (compare_char > 128)
	{
		if (received_character == 0)
		{
			usleep(100);
			kill(*client_pid, SIGUSR1);
			printf("\n");
			compare_char = 0;
			received_character = 0;
			*compare_pid = 0;
			*client_pid = 0;
		}
		else
		{
			write(1, &received_character, 1);
			compare_char = 0;
			received_character = 0;
			usleep(100);
		}
	}
}
