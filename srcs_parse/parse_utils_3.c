/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:45:28 by dvergobb          #+#    #+#             */
/*   Updated: 2022/05/07 18:53:55 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	d_syntax_error(char *error)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("'\n", 2);
	return (EXIT_FAILURE);
}

int	d_check_end(char *input)
{
	int	i;
	int	j;

	j = 0;
	i = ft_strlen(input) - 1;
	while (input[j] && input[j] == ' ')
		j++;
	if (i >= 0)
	{
		while (i >= 0 && input[i] == ' ')
			i--;
		if (i < 0)
			return (EXIT_FAILURE);
		if (input[i] == '<' || input[i] == '>')
			return (d_syntax_error("newline"));
		if (input[j] == '|' || (input[i] == '|' && i == j))
			return (d_syntax_error("|"));
		if (input[i] == '|')
			return (d_syntax_error("|"));
	}
	return (d_check_heredoc(input));
}

int	d_check_quote(char *input, char c)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (input[++i])
	{
		if (input[i] == c && d_count_bf(input, i) == EXIT_SUCCESS)
		{
			count++;
			i++;
			while (input[i] && input[i] != c)
				i++;
			if (input[i] == c)
				count++;
		}
	}
	if (count % 2 != 0)
		return (ft_putstr_fd("syntax error : quote unclosed\n", 2));
	return (EXIT_SUCCESS);
}

int	d_count_bf(char *s, int i)
{
	int	j;
	int	c_sp;
	int	c_db;

	j = -1;
	c_sp = 0;
	c_db = 0;
	while (s[++j] && j < i)
	{
		if (s[j] == '\'' && c_db % 2 == 0)
			c_sp++;
		if (s[j] == '\"' && c_sp % 2 == 0)
			c_db++;
	}
	if (c_sp % 2 == 0 && c_db % 2 == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	d_empty_cmd(char **tb)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	while (tb[++i])
	{
		j = -1;
		count = 0;
		while (tb[i][++j])
			if ((tb[i][j] < 8 || tb[i][j] > 13) && tb[i][j] != 32)
				count += tb[i][j];
		if (count == 0)
			return (1);
	}
	return (0);
}
