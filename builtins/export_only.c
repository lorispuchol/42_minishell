/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_only.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:13:43 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/05 20:31:55 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_sort_ascii(char **tab_env)
{
	int		i;
	int		j;
	char	*strtamp;
	int		size_tab;

	i = 0;
	while (tab_env[i])
		i++;
	size_tab = i;
	i = 0;
	strtamp = "0";
	j = -1;
	while (++j < size_tab - 1)
	{
		if (l_strcmp(tab_env[j], tab_env[j + 1]) > 0)
		{
			strtamp = tab_env[j];
			tab_env[j] = tab_env[j + 1];
			tab_env[j + 1] = strtamp;
			j = -1;
		}
	}
	return (tab_env);
}

char	**convert_in_tab(t_env *env)
{
	int		i;
	char	**tab_env;
	t_env	*tmp;

	tmp = env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (!i)
		return (NULL);
	tab_env = ft_xmalloc(sizeof(char *) * (i + 1));
	tab_env[i] = NULL;
	tmp = env;
	i = 0;
	while (tmp)
	{
		tab_env[i] = tmp->str;
		tmp = tmp->next;
		i++;
	}
	tab_env = ft_sort_ascii(tab_env);
	return (tab_env);
}

void	bt_export_only(t_cmds *cmds, int i, int j, int open)
{
	char	**tab_env;

	tab_env = NULL;
	tab_env = convert_in_tab(cmds->ptr_mnsh->lst_env);
	if (!tab_env)
		return ;
	while (tab_env[++i])
	{
		if (l_strncmp(tab_env[i], "_=", 2) != 0)
		{
			ft_putstr_fd("declare -x ", cmds->fd_outfile);
			while (tab_env[i][++j])
			{
				write(cmds->fd_outfile, &tab_env[i][j], 1);
				if (tab_env[i][j] == '=')
					open = (0 * (write(cmds->fd_outfile, "\"", 1)) + 1);
			}
			j = -1;
			if (open == 1)
				open = 0 * (write(cmds->fd_outfile, "\"", 1));
			write(cmds->fd_outfile, "\n", 1);
		}
	}
	free(tab_env);
	tab_env = NULL;
}
