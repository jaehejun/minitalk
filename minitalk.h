/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:17:56 by jaehejun          #+#    #+#             */
/*   Updated: 2023/08/05 19:35:56 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

// utils functions for minitalk
int		is_space(char c);
int		ft_atoi(const char *str);
void	ft_putnbr(int n);
void	ft_putchar(char format);
void	check_sending_signal(int check_sending);

// functions for server
void	receive_signal(int signum);
void	receive_string(int signum, int *c_pid, int *compare_pid);
void	print_character(int *c_pid, int *bit_pid, int *bit_char, int *one_char);

// functions for client
void	receive_server_signal(int signum);
void	send_pid(int server_pid, int c_pid);
void	send_message(int server_pid, char *message);
void	send_terminating_signal(int server_pid);

#endif