/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:44:35 by jaehejun          #+#    #+#             */
/*   Updated: 2023/08/03 13:38:49 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void    send_message(int server_pid, char *message)
{
    int    compare_bit;
    int    message_index;

    message_index = 0;
    compare_bit = 1;
    while (message[message_index] != '\0')
    {
        while (compare_bit <= 128)
        {
            //printf("%d\n", compare_bit);
            if ((message[message_index] & compare_bit) == 1)
            {
                kill(server_pid, SIGUSR1);
            }
            else
                kill(server_pid, SIGUSR2);
            usleep(50);
            compare_bit = compare_bit << 1;
            printf("%d\n", compare_bit);
        }
        message_index++;
    }
    return ;
}

int main(int argc, char* argv[])
{
    int     server_pid;
    char    *message;
    
    // client parameter check
    if (argc != 3)
	{
        printf("Usage: ./client <server_pid> <string_to_send>\n");
        exit(0);
    }
    // server_pid check
    server_pid = atoi(argv[1]);
    if (server_pid <= 100 || server_pid > 99999)
    {
        printf("Invalid PID\n");
        exit(0);
    }
    message = argv[2];
    printf("%s\n", message);
    send_message(server_pid, message);
    return (0);
}


    
    
//    int message_index = 0;
    



//    while (message[message_index] != '\0')
//	{
//        int bit_index = 0;
//        while (bit_index < 8)
//		{
//            int signal_to_send;
//            int current_bit = (1 << bit_index);
//            while(1) 
//			{
//                if (message[message_index] & current_bit)
//				{
//                    signal_to_send = SIGUSR2;
//                }
//				else
//				{
//                    signal_to_send = SIGUSR1;
//                }
//                break;
//            }
//            kill(server_pid, signal_to_send);
//            usleep(50);
//            bit_index++;
//        }
//        message_index++;
//    }
//    return 0;
//}
