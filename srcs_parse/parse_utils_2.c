/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:16:10 by dvergobb          #+#    #+#             */
/*   Updated: 2022/05/04 07:21:09 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = s;
	while (n-- >= 0)
		*str++ = 0;
}

void	ft_free_tab(char **tb)
{
	int	i;

	i = -1;
	if (!tb)
		return ;
	while (tb[++i])
	{
		free(tb[i]);
		tb[i] = NULL;
	}
	free(tb);
	tb = NULL;
}

void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;

	str = s;
	while (n-- >= 0)
		*str++ = (unsigned char)c;
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*arr;
	size_t	i;

	i = 0;
	arr = ft_xmalloc(nmemb * (size + 1));
	while (i < nmemb)
	{
		arr[i] = '\0';
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char	*d_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ret;

	if (!s1)
	{
		s1 = ft_calloc(1, sizeof(char));
		if (!s1)
			return (0);
	}
	i = -1;
	j = -1;
	ret = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!ret)
		return (0);
	while (s1[++i])
		ret[++j] = s1[i];
	i = -1;
	while (s2[++i])
		ret[++j] = s2[i];
	free(s1);
	s1 = NULL;
	return (ret);
}
