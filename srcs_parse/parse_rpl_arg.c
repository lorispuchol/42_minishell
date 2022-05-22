/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rpl_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 10:29:00 by dvergobb          #+#    #+#             */
/*   Updated: 2022/05/06 17:24:16 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*d_get_arg_name(char *s, int i)
{
	int		j;
	int		len;
	char	*name;

	len = 0;
	while (s[i] && s[i] != '$')
		i++;
	if (s[i] == '$')
	{
		i++;
		while (s[i] && s[i] != '$' && s[i] != ' '
			&& s[i] != '\'' && s[i] != '\"')
		{
			len++;
			i++;
		}
	}
	name = ft_calloc(len + 1, sizeof(char));
	j = i - len - 1;
	i = -1;
	while (++i < len)
		name[i] = s[++j];
	return (name);
}

static char	*d_get_arg_value(char *name, char **env)
{
	int		i;
	int		j;
	int		len;
	char	*value;

	len = ft_strlen(name);
	if (l_strcmp(name, "?") == 0)
		return (l_itoa(g_xcode[0]));
	i = -1;
	while (env[++i])
	{
		if (d_strncmp(name, env[i], len) == 0 && env[i][len] == '=')
		{
			value = ft_calloc(ft_strlen(env[i]) - len + 1, sizeof(char));
			j = -1;
			while (env[i][++len])
				value[++j] = env[i][len];
			return (value);
		}
	}
	value = ft_calloc(0, sizeof(char));
	return (d_clear_empty_quotes(value));
}

static char	*d_strjoin_line(char *s1, char *s2, char *s)
{
	int		i;
	char	*cur;
	char	*line;

	cur = d_strjoin(s1, s2);
	line = ft_calloc(ft_strlen(s) + ft_strlen(s2) + 1, sizeof(char));
	i = -1;
	while (cur[++i])
		line[i] = cur[i];
	free(cur);
	return (line);
}

static char	*d_srch_arg(char *s, char **env, int i)
{
	int		j;
	char	*arg_name;
	char	*arg_value;
	char	*line;

	j = -1;
	line = ft_calloc(ft_strlen(s), sizeof(char));
	while (s[++i])
	{
		if (s[i] == '$' && d_check_quote_pos(s, i) == 0)
		{
			arg_name = d_get_arg_name(s, i);
			arg_value = d_get_arg_value(arg_name, env);
			line = d_strjoin_line(line, arg_value, s);
			j += ft_strlen(arg_value);
			i += ft_strlen(arg_name);
			free(arg_name);
			free(arg_value);
		}
		else
			line[++j] = s[i];
	}
	free(s);
	return (line);
}

char	**d_rpl_arg(char **tb, char **env, int i)
{
	int		j;
	int		count;
	char	**tmp;

	if (!tb)
		return (NULL);
	count = 0;
	while (tb[++i])
		count += d_check_if_arg(tb[i]);
	if (count == 0)
		return (tb);
	tmp = ft_xmalloc(sizeof(char *) * (i + 1));
	tmp[i] = 0;
	i = -1;
	while (tb[++i])
	{
		tmp[i] = ft_calloc(ft_strlen(tb[i]), sizeof(char));
		j = -1;
		while (tb[i][++j])
			tmp[i][j] = tb[i][j];
		if (d_check_if_arg(tmp[i]) > 0)
			tmp[i] = d_srch_arg(tmp[i], env, -1);
	}
	ft_free_tab(tb);
	return (tmp);
}
