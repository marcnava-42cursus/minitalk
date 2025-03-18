/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:46:42 by marcnava          #+#    #+#             */
/*   Updated: 2025/03/17 01:23:05 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	ack_handler(int sig, siginfo_t *info, void *ucontext)
{
	return ;
}

int	main(int argc, char **argv)
{
	struct sigaction	ack;
	int					pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	if (argc != 1)
	{
		ft_printf("Usage: ./server\n");
		return (1);
	}
	ack.sa_sigaction = ack_handler;
	ack.sa_flags = SA_SIGINFO;
	sigemptyset(&ack.sa_mask);
	sigaction(SIGUSR1, &ack, NULL);
	sigaction(SIGUSR2, &ack, NULL);
	while (1)
		pause();
	return (0);
}
