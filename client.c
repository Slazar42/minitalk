/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:27:02 by slazar            #+#    #+#             */
/*   Updated: 2023/03/20 19:48:05 by slazar           ###   ########.fr       */
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
int ft_strlen(char *c)
{
    int i;

    i = 0;
    while (c[i])
        i++;
    return (i);
}

void    message(int sig)
{
    write(1, "sala\n", 5);
    exit(0);
}

void    send_str(char *str, int pid)
{
    int bit;
    int i;
    int j;

    i = 1;
    while (i <= ft_strlen(str))
    {
        bit = 0;
        while (bit < 8)
        {
            if(str[i] & (1 << bit))
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            usleep(300);
            bit++;
        }
        i++;
    }
}

int main(int ac, char **av)
{
    int pid;

    pid = ft_atoi_pid(av[1]);
    signal(SIGUSR1, message);
    if (pid > 0 && ac == 3 )
        send_str(av[2], pid);
    else
    {
        write (1, "\033[91mError: wrong format.\033[0m\n", 26);
		write(1, "\033[33mTry: ./client <PID> <MESSAGE>\033[0m\n",35);
    }
    while (1)
    {
        pause();
    }
    
}
