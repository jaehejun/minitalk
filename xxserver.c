/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:50:56 by jaehejun          #+#    #+#             */
/*   Updated: 2023/08/02 15:52:54 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static int g_current_bit = 0;
static int g_char = 0;

void signal_handler(int signum)
{
    if (signum == SIGUSR1)
		g_char &= ~(1 << g_current_bit);
    else if (signum == SIGUSR2)
		g_char |= (1 << g_current_bit);
    g_current_bit++;

    if (g_current_bit >= 8)
    {
        if (g_char == 10)
        {
            int newline = 10;
            write(1, &newline, 1);
        }
        else
        {
            write(1, &g_char, 1);
        }
        g_char = 0;
        g_current_bit = 0;
    }
}

int main() {
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    printf("Server PID: %d\n", getpid());
    
    while (1) {
        pause();
    }

    return 0;
}
