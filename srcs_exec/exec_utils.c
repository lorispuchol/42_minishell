/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:54:47 by lpuchol           #+#    #+#             */
/*   Updated: 2022/04/26 18:07:12 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*l_strdup(char *s1)
{
	int		i;
	int		len;
	char	*ptr;

	len = ft_strlen(s1);
	ptr = ft_xmalloc(len + 1);
	i = 0;
	while (i <= len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}

char	*l_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	i1;
	size_t	i2;

	i1 = 0;
	i2 = 0;
	if (needle[0] == '\0')
		return (NULL);
	while (haystack[i1] && i1 < len)
	{
		while (haystack[i1 + i2] == needle[i2] && haystack[i1 + i2] != 0
			&& (i1 + i2) < len)
		{
			if (needle[i2 + 1] == '\0' && haystack[i1 + i2 + 1] == '=')
				return (haystack);
			i2++;
		}
		i2 = 0;
		i1++;
	}
	return (NULL);
}

int	l_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	l_strcmp(char *s1, char *s2)
{
	int	n;
	int	renv;

	n = 0;
	renv = 0;
	while (s1[n] != 0 || s2[n] != 0)
	{
		if (s1[n] != s2[n])
		{
			renv = (s1[n] - s2[n]);
			return (renv);
		}
		n++;
	}
	return (renv);
}

int	l_strchr(char *s, char c)
{
	int	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
	{
		if (s[i] == (char)c)
			return (1);
	}
	return (0);
}
