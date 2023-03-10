/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:27:02 by slazar            #+#    #+#             */
/*   Updated: 2023/03/10 20:28:13 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


void    send_char(char *c, int PID)
{
    int i = 7;
    while (*c)
    {

        
        while (i >= 0)
        {
            if(c | (1 << i))
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
            i--;
        }
    
        c++;
    }
    
}

int main(int ac, char **av)
{
    int PID = ft_atoi_pid(av[1]);
    char *string = av[2];

    printf("SERVER PID = %d\n", PID);
    send_char(av[2], PID);
}
