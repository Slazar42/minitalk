/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:23:38 by slazar            #+#    #+#             */
/*   Updated: 2023/03/20 19:48:24 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

void ft_putnbr(int nb)
{
    int i;
    char s;

    if (nb < 0)
    {
        write(1, "-", 1);
        nb = -nb;
    }
    if (nb <= 10)
    {
        s = nb + '0';
        write(1 , &s, 1);
    }
    if (nb >= 10)
    {
        ft_putnbr(nb / 10);
        ft_putnbr(nb % 10);
    }
}

void    ft_handler(int sig, siginfo_t *siga, void *h)
{
    static char c;
    static int  bit;
    int static  pid;
    int         new_pid;

    new_pid = siga->si_pid;
    if (pid != new_pid)
    {
        pid = new_pid;
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
    {
        if (c == '\0')
            kill(pid,SIGUSR1);
        else
            write(1, &c, 1);
        c = 0;
        bit = 0;
    }
}
int main(int ac, char **av)
{ 
    int                 pid ;
    struct sigaction    siga;
    int                 error;

    
    siga.sa_flags = SA_SIGINFO;
    siga.sa_sigaction = ft_handler;
    sigemptyset(&siga.sa_mask);
    (void)av;
    if (ac != 1)
    {
        write(1, "\033[91mError: wrong format.\n\033[0m",26);
		write(1, "\033[33mTry: ./server\n\033[0m", 19);
		return (0);
    }
    pid = getpid();
    write(1, "\033[94mPID\033[0m->", 20);
    ft_putnbr(pid);
	error = sigaction(SIGUSR1, &siga, NULL);
	error = sigaction(SIGUSR2, &siga, NULL);
	if (error != 0)
		return (1);
    while (ac == 1)
        pause();
}