/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:23:17 by lpuchol           #+#    #+#             */
/*   Updated: 2022/04/15 19:17:04 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	l_free_split(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
	{
		free(tabl[i]);
		tabl[i] = NULL;
		i++;
	}
	if (tabl)
	{
		free (tabl);
		tabl = NULL;
	}
	return (0);
}

int	l_nb_word(char *s, char c)
{
	int	i;
	int	nb_word;

	nb_word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			nb_word++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (nb_word);
}

static int	l_alloc(char **tabl, char *s, char c, int nb_word)
{
	int	i;
	int	n;
	int	size_word;

	i = 0;
	n = 0;
	size_word = 0;
	while (i < nb_word)
	{
		while (s[n] && s[n] == c)
			n++;
		while (s[n] && s[n] != c)
		{
			n++;
			size_word++;
		}
		if (size_word != 0)
			tabl[i] = malloc((size_word + 1) * sizeof(char));
		if (!tabl[i])
			return (l_free_split(tabl));
		size_word = 0;
		i++;
	}
	return (1);
}

static void	l_fill(char **tabl, char *s, char c, int nb_word)
{
	int	i1;
	int	i2;
	int	n;

	i1 = 0;
	i2 = 0;
	n = 0;
	while (i1 < nb_word)
	{
		while (s[n] && s[n] == c)
			n++;
		while (s[n] && s[n] != c)
		{
			tabl[i1][i2] = s[n];
			i2++;
			n++;
		}
		tabl[i1][i2] = '\0';
		i2 = 0;
		i1++;
	}
}

char	**l_split(char *s, char c)
{
	int		nb_word;
	char	**tabl;
	int		test;

	test = 0;
	nb_word = 0;
	if (!s)
		return (NULL);
	nb_word = l_nb_word(s, c);
	tabl = ft_xmalloc((nb_word + 1) * sizeof(char *));
	test = l_alloc(tabl, s, c, nb_word);
	if (test == 0)
		exit (1);
	l_fill(tabl, s, c, nb_word);
	tabl[nb_word] = 0;
	return (tabl);
}
