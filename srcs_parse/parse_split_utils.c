/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:13:23 by dvergobb          #+#    #+#             */
/*   Updated: 2022/05/03 15:40:27 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	d_count_word_loop(const char *str, char c, int i)
{
	while (str[i] && str[i] != c)
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			i++;
		}
		else
			i++;
	}
	return (i);
}

int	d_malloc_loop(const char *str, int i)
{
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		i++;
	}
	else if (str[i] == '\"')
	{
		i++;
		while (str[i])
			i++;
		i++;
	}
	return (i);
}

int	d_fill_loop(const char *str, char **tb, t_vars *ijk)
{
	int	i;
	int	j;
	int	k;

	i = ijk->i;
	j = ijk->j;
	k = ijk->k;
	if (str[i] == '\'')
	{
		tb[j][k++] = str[i++];
		while (str[i] && str[i] != '\'')
			tb[j][k++] = str[i++];
		tb[j][k++] = str[i++];
	}
	else if (str[i] == '\"')
	{
		tb[j][k++] = str[i++];
		while (str[i] && str[i] != '\"')
			tb[j][k++] = str[i++];
		tb[j][k++] = str[i++];
	}
	else
		tb[j][k++] = str[i++];
	return (k);
}

int	d_skip_loop(const char *str, int j)
{
	int	i;

	i = j;
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		i++;
	}
	else if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		i++;
	}
	else
		i++;
	return (i);
}
