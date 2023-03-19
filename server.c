/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:23:38 by slazar            #+#    #+#             */
/*   Updated: 2023/03/19 17:15:58 by slazar           ###   ########.fr       */
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

void    ft_handler(int sig, siginfo_t *i, void *h)
{
    static char c[4];
    static int  bit;
    int static  pid;
    int         new_pid;
    static int  count;
    static int  k;

    new_pid = i->si_pid;
    if (pid != new_pid)
    {
        pid = new_pid;
        c[count] = 0;
        bit = 0;
    }
    if (sig == SIGUSR1)
    {
        c[count] = c[count] | (1 << bit);
        if (bit < 4 && bit == k)
            k++;
        bit++;   
    }
    else if (sig == SIGUSR2)
        bit++;
    if (bit == 32 && k == 4)
    {
        write(1, c, 4);
        // write(1, "2", 1);
        c[0] = 0;
        c[1] = 0;
        c[2] = 0;
        c[3] = 0;
        bit = 0;
        k = 0;
    }
    if (bit == 24 && k == 3)
    {
        write(1, c, 3);
        // write(1, "3", 1);
        c[0] = 0;
        c[1] = 0;
        c[2] = 0;
        bit = 0;
        k = 0;
    }
    if (bit == 16 && k == 2)
    {
        write(1,  &c, 2);
        // write(1, "1", 1);
        c[0] = 0;
        c[1] = 0;
        bit = 0;
        k = 0;
    }
    if (bit == 8 && k == 0)
    {
        // write(1, "0", 1);
        write(1, c, 1);
        c[0] = 0;
        bit = 0;
    }
    if ((bit == 8 || bit == 16 || bit == 24 || bit == 32) && (k < 4 && k > 1))
        count++;
}
int main(int ac, char **av)
{
    int pid ;
    struct sigaction siga;
    
    siga.sa_flags = SA_SIGINFO;
    siga.sa_sigaction = ft_handler;
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
    write(1, "\033[86m\nWaiting for a message...\n\033[0m", 38);
    sigaction(SIGUSR1, &siga, NULL);
    sigaction(SIGUSR2, &siga, NULL);
    while (ac == 1)
        pause();
}