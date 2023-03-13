/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:23:38 by slazar            #+#    #+#             */
/*   Updated: 2023/03/13 06:03:30 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>


void putnbr(int nb)
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
        putnbr(nb/10);
        putnbr(nb%10);
    }
}

void    handler(int sig)
{
    static char c = 0;
    static int bit = 0;

    if(sig == SIGUSR1)
    {
        c = c | (1 << bit);
        bit++;   
    }
    else if (sig == SIGUSR2)
        bit++;
    if(bit == 8)
    {
        write(1, &c, 1);
        c = 0;
        bit = 0;
    }
}

int main(int ac, char **av)
{
    int pid ;

    (void)av;
    if (ac != 1)
    {
        write(1, "\033[91mError: wrong format.\033[0m",25);
        write(1, "\n", 1);
		write(1, "\033[33mTry: ./server\033[0m", 18);
		return (0);
    }
    
    pid = getpid();
    write(1, "\033[94mPID\033[0m \033[96m->\033[0m %d\n", 15);
    putnbr(pid);
    write(1, "\033[0mWaiting for a message...\033[0m\n", 31);
    write(1, "\n", 1);

    while (ac == 1)
    {
        signal(SIGUSR1,handler);
        signal(SIGUSR2,handler);
        pause();
    }
}