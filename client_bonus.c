/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:27:02 by slazar            #+#    #+#             */
/*   Updated: 2023/03/24 17:34:24 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi_pid(char *str)
{
	int	s;

	s = 0;
	while (*str && (*str == ' ' | *str == '\t'))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		s = s * 10 + (*str - '0');
		str++;
	}
	if (!(*str >= '0' && *str <= '9') && *str)
		return (-1);
	return (s);
}

int	ft_strlen(char *c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

void	message(int sig)
{
	(void)sig;
	write (1, "\n  \033[1m\033[32:5:5m[SUCCESSE]  message reseved.\n\n", 46);
	exit (0);
}

void	send_str(char *str, int pid)
{
	int	bit;
	int	i;

	i = 0;
	while (i <= ft_strlen(str))
	{
		bit = 0;
		while (bit < 8)
		{
			if (str[i] & (1 << bit))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(300);
		bit++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int	pid;

	signal(SIGUSR1, message);
	if (ac == 3)
	{
		pid = ft_atoi_pid(av[1]);
		if (pid > 0)
			send_str(av[2], pid);
		else
		{
			write (1, "\033[91mError Pid\n", 15);
			exit (0);
		}
	}
	else if (ac != 3)
	{
		write (1, "\033[91mError: wrong format.\n", 26);
		write(1, "\033[33mTry: ./client <PID> <MESSAGE>\033[0m\n", 35);
		exit(0);
	}
	while (1)
		pause();
}
