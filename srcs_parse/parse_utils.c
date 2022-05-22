/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:16:10 by dvergobb          #+#    #+#             */
/*   Updated: 2022/05/02 19:52:13 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_putstr_fd(char *s, int fd)
{
	return (write(fd, s, ft_strlen(s)));
}

int	d_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	*s1c;
	unsigned char	*s2c;

	i = 0;
	s1c = (unsigned char *)s1;
	s2c = (unsigned char *)s2;
	while (n--)
	{
		if (s1c[i] != s2c[i] || s1c[i] == 0 || s2c[i] == 0)
			return (s1c[i] - s2c[i]);
		i++;
	}
	return (0);
}

int	d_check_quote_pos(char *s, int i)
{
	int	j;
	int	c_sp;
	int	c_db;

	j = -1;
	c_sp = 0;
	c_db = 0;
	while (s[++j] && j <= i)
	{
		if (s[j] == '\"' && d_count_bf(s, i) != 0)
			c_db++;
		if (s[j] == '\'' && d_count_bf(s, i) != 0 && c_db % 2 == 0)
			c_sp++;
	}
	return (c_sp % 2);
}

int	d_check_if_arg(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1])
		{
			if (s[i + 1] != ' '
				&& s[i + 1] != '\''
				&& s[i + 1] != '\"'
				&& s[i + 1] != '|'
			)
				count++;
		}
		i++;
	}
	return (count);
}
