/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:45:28 by dvergobb          #+#    #+#             */
/*   Updated: 2022/05/07 17:37:16 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	d_quote_first_level(char *s, int i)
{
	int	j;
	int	c_sp;
	int	c_db;

	j = -1;
	c_sp = 0;
	c_db = 0;
	while (s[++j] && j < i)
	{
		if (s[j] == '\"' && c_sp % 2 == 0)
			c_db++;
		if (s[j] == '\'' && c_db % 2 == 0)
			c_sp++;
	}
	if ((s[i] == '\'' && c_db % 2 != 0) || (s[i] == '\"' && c_sp % 2 != 0))
		return (1);
	return (0);
}

char	*d_clear_empty_quotes(char *s)
{
	char	*line;
	int		count;
	int		len;
	int		i;
	int		j;

	i = -1;
	count = 0;
	len = ft_strlen(s);
	while (s[++i])
		if ((s[i] == '\'' || s[i] == '\"'))
			if (d_quote_first_level(s, i) == 1)
				count++;
	if (count == 0)
		return (s);
	i = -1;
	j = -1;
	line = ft_calloc(len - count, sizeof(char));
	while (s[++i])
		if (((s[i] == '\'' || s[i] == '\"') && d_quote_first_level(s, i) != 0)
			|| !(s[i] == '\'' || s[i] == '\"'))
			line[++j] = s[i];
	free(s);
	s = NULL;
	return (line);
}

char	*d_clear_quote(char *s)
{
	char	*line;
	int		i;
	int		len;

	i = 0;
	line = NULL;
	len = ft_strlen(s) - 1;
	if (s[0] == '\'' && s[len] == '\'')
	{
		line = ft_calloc(len - 1, sizeof(char));
		while (++i < len)
			line[i - 1] = s[i];
		free(s);
		return (d_clear_empty_quotes(line));
	}
	else if (s[0] == '\"' && s[len] == '\"')
	{
		line = ft_calloc(len - 1, sizeof(char));
		while (++i < len)
			line[i - 1] = s[i];
		free(s);
		return (d_clear_empty_quotes(line));
	}
	return (d_clear_empty_quotes(s));
}

char	**d_sprim(char *tb)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = d_split(tb, ' ');
	while (tmp[++i])
		tmp[i] = d_clear_quote(tmp[i]);
	return (tmp);
}
