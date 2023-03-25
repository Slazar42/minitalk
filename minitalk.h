/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:25:12 by slazar            #+#    #+#             */
/*   Updated: 2023/03/25 18:14:04 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <signal.h>
# include <unistd.h>

void	ft_handler(int sig, siginfo_t *siga, void *h);
void	ft_putnbr(int nb);
int		ft_atoi_pid(char *str);
void	send_str(char *str, int pid);
void	message(int sig);
int		ft_strlen(char *c);

#endif
