/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:45:28 by dvergobb          #+#    #+#             */
/*   Updated: 2022/05/07 18:37:43 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_tab_len(char	**tb)
{
	int	i;

	i = 0;
	if (!tb || !tb[0])
		return (0);
	while (tb[i])
		i++;
	return (i);
}

static int	d_too_much_pipe(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[++i] && input[i - 1] && ft_strlen(input) > 2)
		if (input[i] == '|' && input[i - 1] == '|')
			count++;
	return (count);
}

static int	d_parse_struct(t_minishell *mnsh, int len, char **tmp, int i)
{
	char	**cmds;

	while (tmp[++i])
		if (d_check_end(tmp[i]) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	mnsh->cmds = (t_cmds *)ft_xmalloc(sizeof(t_cmds) * (len + 1));
	i = -1;
	while (tmp[++i])
	{
		cmds = d_sprim(tmp[i]);
		mnsh->cmds[i].cmd = d_without_redirections(cmds, -1, -1);
		mnsh->cmds[i].infile = d_get_infile(cmds);
		mnsh->cmds[i].outfile = d_get_outfile(cmds);
		mnsh->cmds[i].intype = d_get_intype(cmds);
		mnsh->cmds[i].index_cmd = i;
		mnsh->cmds[i].ptr_mnsh = mnsh;
		free(cmds);
	}
	mnsh->cmds[len].cmd = NULL;
	mnsh->nb_cmd = len;
	ft_free_tab(tmp);
	tmp = NULL;
	return (EXIT_SUCCESS);
}

int	ft_parse(char *input, t_minishell *mnsh)
{
	int		len;
	char	**tmp;

	tmp = NULL;
	if (d_check_end(input) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (d_check_quote(input, '\'') != EXIT_SUCCESS
		|| d_check_quote(input, '\"') != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (d_too_much_pipe(input) > 0)
		return (d_syntax_error("|"));
	tmp = d_split(input, '|');
	if (d_empty_cmd(tmp) == 1)
	{
		ft_free_tab(tmp);
		return (d_syntax_error("|"));
	}
	tmp = d_cpy_trim(tmp);
	tmp = d_rpl_arg(tmp, mnsh->tab_env, -1);
	len = ft_tab_len(tmp);
	return (d_parse_struct(mnsh, len, tmp, -1));
}
