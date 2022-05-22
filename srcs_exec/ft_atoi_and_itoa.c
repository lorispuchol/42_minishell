/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_and_itoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:03:32 by lpuchol           #+#    #+#             */
/*   Updated: 2022/04/26 18:05:43 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	l_atoi(const char *str)
{
	long	ret;
	int		i;
	int		signe;

	signe = 1;
	ret = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -signe;
		i++;
	}
	while (str[i] && l_isdigit(str[i]) == 1)
	{
		ret = ret * 10 + str[i] - 48;
		if (ret > 2147483648 && signe == -1)
			return (0);
		if (ret > 2147483647 && signe == 1)
			return (-1);
		i++;
	}
	return (ret * signe);
}

static int	ft_size_needed(int n)
{
	int	size_str;

	size_str = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		size_str++;
		n = n * (-1);
	}
	while (n >= 10)
	{
		n = n / 10;
		size_str++;
	}
	return (size_str);
}

static void	ft_rempli(char *str, long n)
{
	int	i;

	i = ft_size_needed(n) - 1;
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (i >= 0 && str[i] != '-')
	{
		str[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
}

char	*l_itoa(int n)
{
	char	*str;

	if (n == 0)
	{
		str = l_calloc(2, 1);
		if (!str)
			return (NULL);
		str[0] = '0';
		return (str);
	}
	str = l_calloc(ft_size_needed(n) + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_rempli(str, n);
	return (str);
}
