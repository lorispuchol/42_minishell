/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 12:20:10 by dvergobb          #+#    #+#             */
/*   Updated: 2022/05/06 11:33:18 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	d_count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			while (s[i] && s[i] == c)
				i++;
		else
		{
			count++;
			i = d_count_word_loop(s, c, i);
		}
	}
	return (count);
}

static int	ft_malloc_words_ext(char const *s, char c, int i)
{
	while (s[i] == c)
		i++;
	return (i);
}

static void	ft_malloc_words(char const *s, char c, char **tb, int j)
{
	int	len;
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i = ft_malloc_words_ext(s, c, i);
		else
		{
			while (s[i])
			{
				if (s[i] == c)
					i = ft_malloc_words_ext(s, c, i);
				else
				{
					len = i;
					i = d_count_word_loop(s, c, i);
					tb[j++] = ft_calloc(i - len + 1, sizeof(char));
				}
			}
		}
	}
	tb[j] = 0;
}

static void	ft_fill_tb(char const *s, char c, char **tb)
{
	t_vars	*ijk;

	ijk = ft_xmalloc(sizeof(t_vars *) * 2);
	ijk->i = 0;
	ijk->j = 0;
	ijk->k = 0;
	while (s[ijk->i])
	{
		if (s[ijk->i] == c && s[ijk->i])
			while (s[ijk->i] == c && s[ijk->i])
				ijk->i++;
		else
		{
			while (s[ijk->i] && s[ijk->i] != c)
			{
				ijk->k = d_fill_loop(s, tb, ijk);
				ijk->i = d_skip_loop(s, ijk->i);
			}
			ijk->j++;
			ijk->k = 0;
		}
	}
	free(ijk);
}

char	**d_split(char const *s, char c)
{
	char	**tb;
	int		len;

	if (!s)
		return (NULL);
	len = d_count_words(s, c);
	tb = ft_xmalloc(sizeof(char *) * (len + 1));
	tb[len] = NULL;
	ft_malloc_words(s, c, tb, 0);
	ft_fill_tb(s, c, tb);
	return (tb);
}
