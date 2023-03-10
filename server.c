/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:23:38 by slazar            #+#    #+#             */
/*   Updated: 2023/03/10 17:47:51 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>

static int i = 7;
static char c = 0;

void    hundlilina(int sig)
{
    while (i >= 0)
    {
        if(sig == SIGUSR1)
        {
            c = c & (1 << i);
            i--;   
        }
        else
            i--;
    }
    if(i == 0)
        write(1, &c, 1);
}
int main()
{
    int PID = getpid();
    printf("%d",PID);
    printf("----------");
    while (1)
    {
        signal(SIGUSR1,hundlilina);
        signal(SIGUSR2,hundlilina);
    }
}