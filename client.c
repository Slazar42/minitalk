/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:27:02 by slazar            #+#    #+#             */
/*   Updated: 2023/03/11 18:34:21 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int ft_atoi_pid(char *str)
{
    int s;
    
    s = 0;
    while (*str && (*str == ' ' | *str == '\t'))
        str++;
    if (*str == '-')
    {
        write(1, "please enter a valid PID\n",25);
        return (-1);
    }
    while (*str >= '0' && *str <= '9')
    {
        s = s * 10  + (*str - '0');
        str++;
    }
    if (!(*str >= '0' && *str <= '9') && *str)
    {
        write(1, "please enter a valid PID\n",25);
        return (-1);
    }
    return (s);
}

void    send_char(char *c, int PID)
{
    int bit = 0;
    while (*c)
    {
        while (bit < 8)
        {
            if(*c & (1 << bit))
            {
                kill(PID, SIGUSR1);
                write(1, "1", 1);
            }
            else
            {
                kill(PID, SIGUSR2);    
                write(1, "0", 1);
            }
            usleep(500);
            bit++;
        }
        bit = 0;
        c++;
    }
}

int main(int ac, char **av)
{
    int PID;
    
    PID = ft_atoi_pid(av[1]);
    write(11, "SERVER PID = ", 14);
    // while (*av[2])
    //     write(1, av[2]++, 1);
    send_char(av[2], PID);
}
