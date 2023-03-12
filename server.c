/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:23:38 by slazar            #+#    #+#             */
/*   Updated: 2023/03/12 23:19:30 by slazar           ###   ########.fr       */
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

void    hundlilina(int sig)
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

int main()
{
    int pid ;
    pid = getpid();
    putnbr(pid);
    write(1, "\n----------\n",12);
    signal(SIGUSR1,hundlilina);
    signal(SIGUSR2,hundlilina);
    while (1)
        pause();
}