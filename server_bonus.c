/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:23:38 by slazar            #+#    #+#             */
/*   Updated: 2023/03/24 18:32:13 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
void print_checklast(int *pid, char *c, int *bit)
{
	if (c == '\0')
		kill(*pid, SIGUSR1);
	else
		write(1, c, 1);
	*c = 0;
	*bit = 0;
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
	if (sig == SIGUSR1)
	{
		c = c | (1 << bit);
		bit++;
	}
	else if (sig == SIGUSR2)
		bit++;
	if (bit == 8)
		print_checklast(&pid, &c, &bit);
	
}

void	accc(int ac)
{
	if (ac != 1)
	{
		write(1, "\033[91mError: wrong format.\n\033[0m", 26);
		write(1, "\033[33mTry: ./server\n\033[0m", 19);
		exit (1);
	}
}

int	main(int ac, char **av)
{
	int					pid ;
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
		write (1, "\033[91mError\n", 11);
		exit (0);
	}
	while (ac == 1)
		pause();
}
