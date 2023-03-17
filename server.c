/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:23:38 by slazar            #+#    #+#             */
/*   Updated: 2023/03/17 17:15:58 by slazar           ###   ########.fr       */
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
    if(sig == SIGUSR1)
    {
        c[count] = c[count] | (1 << bit);
        if (bit < 4 && bit == k)
        {
            //write(1, "1\n", 1);
            k++;
            
        }
        bit++;   
    }
    else if (sig == SIGUSR2)
        bit++;
    //printf("k = %d\n", k);
    // printf("bit = %d\n", bit);
    if (bit == 8)
    {
        if(k == 0)
        {
            write(1, &c, 1);
            c[0] = 0;
            bit = 0;
            count = 0;
            k = 0;
        } 
        else
            count++;  
    }
    if (bit == 16)
    {
        printf("count : %d\n", count);
        if(k == 2)
        {
            //write(1, "test16 ins\n", 11);
            write(1, &c, 2);
            c[0] = 0;
            c[1] = 0;
            bit = 0;
            count = 0;
            k = 0;
        } 
        // else
        // {
        //     count++;
        //     //write(1, "tset16\n", 7);
        // }
    }
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