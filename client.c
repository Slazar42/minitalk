/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:27:02 by slazar            #+#    #+#             */
/*   Updated: 2023/03/13 05:59:00 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>


int ft_atoi_pid(char *str)
{
    int s;
    
    s = 0;
    while (*str && (*str == ' ' | *str == '\t'))
        str++;
    while (*str >= '0' && *str <= '9')
    {
        s = s * 10  + (*str - '0');
        str++;
    }
    if (!(*str >= '0' && *str <= '9') && *str)
        return (-1);
    return (s);
}

void    send_str(char *str, int PID)
{
    int bit;

    while (*str)
    {
        bit = 0;
        while (bit < 8)
        {
            if(*str & (1 << bit))
                kill(PID, SIGUSR1);
            else
                kill(PID, SIGUSR2);    
            usleep(100);
            bit++;
        }
        str++;
    }
}

int main(int ac, char **av)
{
    int pid;

    pid = ft_atoi_pid(av[1]);
    if (pid > 0 && ac == 3 )
        send_str(av[2], pid);
    else
    {
        write (1, "\033[91mError: wrong format.\033[0m\n", 26);
        write(1, "\n", 1);
		write(1, "\033[33mTry: ./client <PID> <MESSAGE>\033[0m\n",35);
    }
    if (ac == 3)
    while (*av[2])
        write(1, av[2]++, 1);
}
