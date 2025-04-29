/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:46:45 by marcnava          #+#    #+#             */
/*   Updated: 2025/03/18 18:36:59 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

volatile sig_atomic_t	g_signal = 0;

void	ack_handler(int sig)
{
	(void)sig;
	g_signal = 1;
}

void	send_byte(pid_t server, char byte)
{
	int	bit;

	bit = 8;
	while (bit)
	{
		g_signal = 0;
		if ((byte >> bit) & 1)
			kill(server, SIGUSR2);
		else
			kill(server, SIGUSR1);
		while (!g_signal)
			pause();
		bit--;
		usleep(50);
	}
}

void	send_data(pid_t server, char *data)
{
	while (*data)
	{
		send_byte(server, *data);
		data++;
	}
	send_byte(server, '\0');
}

int	main(int argc, char **argv)
{
	struct sigaction	ack;
	pid_t				server;
	char				*data;

	if (argc != 3)
	{
		ft_printf("Usage: ./client <server pid> <message>\n");
		return (1);
	}
	ack.sa_handler = ack_handler;
	ack.sa_flags = 0;
	sigemptyset(&ack.sa_mask);
	sigaction(SIGUSR2, &ack, NULL);
	server = ft_atoi(argv[1]);
	data = argv[2];
	send_data(server, data);
	return (0);
}
