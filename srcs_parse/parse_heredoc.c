/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:05:30 by dvergobb          #+#    #+#             */
/*   Updated: 2022/05/07 18:57:42 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*d_fill_name(int i)
{
	int		j;
	char	*ret;
	char	*msg;
	char	*name;
	char	*line;

	j = -1;
	name = "/private/tmp/.heredoc";
	line = ft_calloc(ft_strlen(name), sizeof(char));
	while (name[++j])
		line[j] = name[j];
	ret = l_itoa(i);
	msg = d_strjoin(line, ret);
	free(ret);
	return (msg);
}

int	d_check_heredoc(char *tmp)
{
	int		j;
	int		count;
	char	**cmds;
	char	*stop;

	j = -1;
	cmds = d_sprim(tmp);
	count = EXIT_SUCCESS;
	while (cmds[++j])
	{
		if (l_strcmp(cmds[j], "<<") == 0 && cmds[j + 1])
		{
			stop = cmds[j + 1];
			if (l_strcmp(stop, ">") == 0)
				count = d_syntax_error(">");
			if (l_strcmp(stop, "<") == 0)
				count = d_syntax_error("<");
			if (l_strcmp(stop, ">>") == 0)
				count = d_syntax_error(">>");
			if (l_strcmp(stop, "<<") == 0)
				count = d_syntax_error("<<");
		}
	}
	ft_free_tab(cmds);
	return (count);
}

void	d_heredoc_loop(char *stop, int res)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		else if (l_strcmp(stop, input) == 0)
		{
			free(input);
			free(stop);
			break ;
		}
		else
		{
			write(res, input, ft_strlen(input));
			write(res, "\n", 1);
		}
		free(input);
	}
}

char	*d_get_heredoc(char **cmds, int i)
{
	int		res;
	char	*cmd;
	char	*stop;

	stop = cmds[i + 1];
	if (l_strcmp(stop, ">") == 0)
	{
		d_syntax_error(">");
		return (NULL);
	}
	cmd = d_fill_name(i);
	res = open(cmd, O_CREAT | O_TRUNC | O_RDWR, 0666);
	while (res == -1)
	{
		free(cmd);
		cmd = d_fill_name(++i);
		res = open(cmd, O_CREAT | O_TRUNC | O_RDWR, 0666);
	}
	d_heredoc_loop(stop, res);
	close(res);
	return (cmd);
}
