/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmixtur <fmixtur@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:16:21 by fmixtur           #+#    #+#             */
/*   Updated: 2025/03/19 10:17:13 by fmixtur          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     ft_isdigit(int c)
{
        return (c >= '0' && c <= '9');
}

int     ft_atoi(const char *str)
{
        int     i;
        int     minus;
        int     nb;

        nb = 0;
        minus = 1;
        i = 0;
        while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
                i++;
        if (str[i] == '-' || str[i] == '+')
        {
                if (str[i] == '-')
                        minus = -1;
                i++;
        }
        while (ft_isdigit(str[i]))
                nb = nb * 10 + (str[i++]) - '0';
        return (nb * minus);
}