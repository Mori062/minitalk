/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:56:12 by morishitash       #+#    #+#             */
/*   Updated: 2023/07/21 04:05:54 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "../include/minitalk.h"

int	g_ack = STANDBY;

static int	client_error_msg(void)
{
	ft_putendl_fd("\033[31mError", 2);
	ft_putendl_fd(" Usage: ./client [PID] [message]\033[0m", 2);
	return (1);
}


static int	msg_error(void)
{
	ft_putendl_fd("\033[31mError", 2);
	ft_putendl_fd(" Message broken\033[0m", 2);
	return (1);
}

static void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack = STANDBY;
	else
		exit (msg_error());
}

static void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack = STANDBY;
	else
		exit (msg_error());
}

static void	send_char(int pid, char str)
{
	int	i;

	i = 0;
	g_ack = COMPLETE;
	while (i < 8)
	{
		if ((str & (0x01 << i)) != 0)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit (msg_error());
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit (msg_error());
		}
		usleep(50);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	pid;

	i = 0;
	if (argc != 3)
		return (client_error_msg());
	while (argv[1][i] != '\0')
	{
		if (!ft_isdigit(argv[1][i++]))
			return (client_error_msg());
	}
	i = 0;
	pid = ft_atoi(argv[1]);
	if (pid < 0)
		return (client_error_msg());
	signal(SIGUSR1, signal_handler);
	while (argv[2][i] != '\0')
	{
		if (g_ack == STANDBY)
			send_char(pid, argv[2][i++]);
	}
	send_char(pid, '\n');
	return (0);
}
