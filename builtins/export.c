/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:03:43 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/06 17:24:16 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_pos_var(char *var, t_env *lst_env)
{
	char	**var_split;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = lst_env;
	while (tmp)
	{
		var_split = l_split(tmp->str, '=');
		if (l_strcmp(var_split[0], var) == 0)
		{
			ft_free_tab(var_split);
			return (i);
		}
		tmp = tmp->next;
		ft_free_tab(var_split);
		i++;
	}
	return (-1);
}

static void	bt_add_var(char *name_and_value, t_env *lst_env)
{
	t_env	*tmp;

	tmp = lst_env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_xmalloc(sizeof(t_env));
	tmp = tmp->next;
	tmp->str = l_strdup(name_and_value);
	tmp->next = NULL;
}

static void	bt_modif_var(int position, char *name_and_value, t_env *lst_env)
{
	t_env	*tmp;
	int		i;

	i = -1;
	tmp = lst_env;
	while (++i < position && tmp)
		tmp = tmp->next;
	if (tmp->str)
	{
		free (tmp->str);
		tmp->str = NULL;
	}
	tmp->str = l_strdup(name_and_value);
}

void	bt_export(t_cmds *cmds, int i, int pos, char **split_var)
{
	g_xcode[0] = 0;
	if (bt_outfile(cmds) == -1)
		return ;
	if (cmds->cmd[1] == NULL)
		bt_export_only(cmds, -1, -1, 0);
	else
	{
		while (cmds->cmd[++i])
		{
			if (check_valid_var(cmds->cmd[i]) == EXIT_SUCCESS)
			{
				split_var = l_split(cmds->cmd[i], '=');
				pos = get_pos_var(split_var[0], cmds->ptr_mnsh->lst_env);
				if (pos == -1)
					bt_add_var(cmds->cmd[i], cmds->ptr_mnsh->lst_env);
				else if (pos > -1 && (l_strchr(cmds->cmd[i], '=') == 1))
					bt_modif_var(pos, cmds->cmd[i], cmds->ptr_mnsh->lst_env);
				ft_free_tab(split_var);
			}
			else
				g_xcode[0] = 1;
		}
	}
	if (cmds->ptr_mnsh->nb_cmd != 1)
		exit (g_xcode[0]);
}
