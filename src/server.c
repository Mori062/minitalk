/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:56:14 by morishitash       #+#    #+#             */
/*   Updated: 2023/07/21 04:05:13 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../include/minitalk.h"

static int	server_error_msg(void)
{
	ft_putendl_fd("\033[31mError wrong arguments", 2);
	ft_putendl_fd("Usage: ./server \033[0m", 2);
	return (1);
}

static void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int	bit;
	static int	i;

	(void)context;
	if (signal == SIGUSR1)
		i |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		if (kill(info->si_pid, SIGUSR1) == -1)
			exit(server_error_msg());
		bit = 0;
		i = 0;
	}
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("%d\n", getpid());
	act.sa_sigaction = signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_flags = 0;
	sigaddset(&act.sa_mask, SIGUSR2);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
}
