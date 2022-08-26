/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:16:34 by nheo              #+#    #+#             */
/*   Updated: 2022/08/19 15:02:58 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v')
		return (1);
	if (c == '\f' || c == ' ' || c == '\r')
		return (1);
	return (0);
}

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_check_flow(long long num, int c)
{
	c -= '0';
	if (num * 10 + c < num)
		return (1);
	return (0);
}

static void	ft_check_format(const char **str)
{
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '+')
		(*str)++;
}

int	ft_atoi(const char *str)
{
	long long		num;
	int				result;

	num = 0;
	ft_check_format(&str);
	while (ft_isdigit(*str) && *str)
	{
		if (ft_check_flow(num, *str))
			return (-1);
		num *= 10;
		num += *str - '0';
		str++;
	}
	if (*str && !ft_isdigit(*str))
		return (-1);
	result = (int)(num);
	return (result);
}
