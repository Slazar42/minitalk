/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:23:38 by slazar            #+#    #+#             */
/*   Updated: 2023/03/25 19:40:31 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "stdio.h"

void	ft_putnbr(int nb)
{
	char	s;

	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb <= 10)
	{
		s = nb + '0';
		write(1, &s, 1);
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}

void	ft_send_signal(int sig, int *bit, char *c)
{
	if (sig == SIGUSR1)
	{
		*c = *c | (1 << *bit);
		*bit = *bit +1;
	}
	else if (sig == SIGUSR2)
		*bit = *bit +1;
}

void	ft_handler(int sig, siginfo_t *siga, void *h)
{
	static char	c;
	static int	bit;
	int static	pid;

	(void)h;
	if (pid != siga->si_pid)
	{
		pid = siga->si_pid;
		c = 0;
		bit = 0;
	}
	ft_send_signal(sig, &bit, &c);
	if (bit == 8)
	{
		if (c == '\0')
			kill(pid, SIGUSR1);
		else
			write(1, &c, 1);
		c = 0;
		bit = 0;
	}
}

void	accc(int ac)
{
	if (ac != 1)
	{
		write(1, "\033[91mError: wrong format.\n\033[0m", 26);
		write(1, "\033[33mTry: ./server_bonus\n\033[0m", 25);
		exit(1);
	}
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	siga;
	int					error;

	accc(ac);
	(void)av;
	siga.sa_flags = SA_SIGINFO;
	siga.sa_sigaction = ft_handler;
	sigemptyset(&siga.sa_mask);
	pid = getpid();
	write(1, "PID->", 5);
	ft_putnbr(pid);
	write(1, "\n", 1);
	error = sigaction(SIGUSR1, &siga, NULL);
	error = sigaction(SIGUSR2, &siga, NULL);
	if (error != 0)
	{
		write(1, "\033[91mError\n", 11);
		exit(0);
	}
	while (ac == 1)
		pause();
}
