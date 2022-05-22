/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:45:28 by dvergobb          #+#    #+#             */
/*   Updated: 2022/05/21 11:57:42 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*d_get_outfile(char **cmds)
{
	int		i;
	int		res;
	char	*cmd;

	i = -1;
	res = 0;
	cmd = NULL;
	while (cmds[++i])
	{
		if ((l_strcmp(cmds[i], ">") == 0 || l_strcmp(cmds[i], ">>") == 0)
			&& cmds[i + 1])
		{
			if (l_strcmp(cmds[i], ">") == 0)
				res = open(cmds[++i], O_CREAT | O_TRUNC | O_RDONLY, 0666);
			else if (l_strcmp(cmds[i], ">>") == 0)
				res = open(cmds[++i], O_CREAT | O_RDONLY, 0666);
			if (res == -1)
				return (cmds[i]);
			else
				close(res);
			cmd = cmds[i];
		}
	}
	return (cmd);
}

char	*d_get_infile(char **cmds)
{
	int		i;
	int		res;
	char	*cmd;

	i = -1;
	cmd = NULL;
	while (cmds[++i])
	{
		if (l_strcmp(cmds[i], "<<") == 0 && cmds[i + 1])
			cmd = d_get_heredoc(cmds, i);
		else if (l_strcmp(cmds[i], "<") == 0 && cmds[i + 1])
		{
			i++;
			res = open(cmds[i], O_RDONLY);
			if (res == -1)
				return (cmds[i]);
			else
				close(res);
			cmd = cmds[i];
		}
	}
	return (cmd);
}

int	d_get_intype(char **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
	{
		if (l_strcmp(cmds[i], ">") == 0 && cmds[i + 1])
		{
			free(cmds[i]);
			return (1);
		}
		else if (l_strcmp(cmds[i], ">>") == 0 && cmds[i + 1])
		{
			free(cmds[i]);
			return (2);
		}
	}
	free(cmds[i]);
	return (0);
}

static int	d_is_file(char *file)
{
	if (l_strcmp(file, ">") == 0)
		return (1);
	if (l_strcmp(file, ">>") == 0)
		return (1);
	if (l_strcmp(file, "<") == 0)
		return (1);
	return (0);
}

char	**d_without_redirections(char **tmp, int i, int j)
{
	char	**analyzed;

	if (l_strcmp(tmp[0], "<<") == 0)
	{
		analyzed = ft_xmalloc((ft_tab_len(tmp) - 1) * sizeof(char *));
		free(tmp[0]);
		analyzed[++j] = NULL;
		if (tmp[2])
			analyzed[j] = tmp[2];
		i = 2;
		while (tmp[++i])
			analyzed[++j] = tmp[i];
		analyzed[++j] = NULL;
		return (analyzed);
	}
	analyzed = ft_xmalloc((ft_tab_len(tmp) + 1) * sizeof(char *));
	while (tmp[++i])
	{
		if (!d_is_file(tmp[i]))
			analyzed[++j] = tmp[i];
		else if (tmp[i + 1])
			i++;
	}
	analyzed[++j] = NULL;
	return (analyzed);
}
