/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:54:49 by dvergobb          #+#    #+#             */
/*   Updated: 2022/04/18 17:09:42 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	d_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char	*d_trim(char *s)
{
	char	*line;
	int		len;
	int		i;
	int		j;

	i = -1;
	len = ft_strlen(s);
	while (d_is_space(s[++i]))
		len--;
	i = ft_strlen(s);
	while (d_is_space(s[--i]))
		len--;
	line = ft_calloc(len, sizeof(char));
	i = 0;
	j = -1;
	while (d_is_space(s[i]))
		i++;
	while (j < len - 1)
		line[++j] = s[i++];
	line[++j] = '\0';
	return (line);
}

char	**d_cpy_trim(char **tb)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = NULL;
	if (!tb)
		return (NULL);
	i = 0;
	j = -1;
	while (tb[i])
		i++;
	tmp = ft_xmalloc(sizeof(char *) * (i + 1));
	while (tb[++j])
		tmp[j] = d_trim(tb[j]);
	tmp[j] = 0;
	ft_free_tab(tb);
	tb = NULL;
	return (tmp);
}
