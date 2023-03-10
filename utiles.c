/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:50:22 by slazar            #+#    #+#             */
/*   Updated: 2023/03/10 20:13:22 by slazar           ###   ########.fr       */
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
    if (!(*str >= '0' && *str <= '9') && !(*str == ' ' | *str == '\t'))
    {
        write(1, "please enter a valid PID\n",25);
        return (-1);
    }
    return (s);
}
int main ()
{
printf("%d",ft_atoi_pid("       556   "));

}