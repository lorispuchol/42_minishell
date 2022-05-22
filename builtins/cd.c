/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:58:48 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/06 17:24:16 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_value(int position, t_env *lst_env)
{
	int		i;
	t_env	*tmp;

	tmp = lst_env;
	i = -1;
	while (++i < position && tmp)
		tmp = tmp->next;
	if (l_strchr(tmp->str, '=') == 0)
	{
		g_xcode[0] = 1;
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	i = 0;
	while (tmp->str[i] && tmp->str[i] != '=')
		i++;
	if (tmp->str[i] != '=')
	{
		g_xcode[0] = 1;
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	if (!tmp->str[i + 1])
		return (NULL);
	return (&tmp->str[i + 1]);
}

static int	get_position_var(char *var, t_env *lst_env)
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

/*
	
	=> UNUSED FUNCTIONS

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
*/

static void	cd_with_arg(t_cmds *cmds)
{
	if (cmds->cmd[1])
	{	
		if (chdir(cmds->cmd[1]) == -1)
		{
			g_xcode[0] = 1;
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(cmds->cmd[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
			change_pwds(cmds, 0, NULL);
	}
	if (cmds->ptr_mnsh->nb_cmd != 1)
		exit(g_xcode[0]);
}

void	bt_cd(t_cmds *cmds)
{
	int		position;
	char	*path;

	g_xcode[0] = 0;
	if (!cmds->cmd[1])
	{
		position = get_position_var("HOME", cmds->ptr_mnsh->lst_env);
		if (position == -1)
			g_xcode[0] = ((0 * ft_putstr_fd("minishell: cd: HOME not set\n",
							2)) + 1);
		else
		{
			path = get_value(position, cmds->ptr_mnsh->lst_env);
			if (path != NULL)
			{
				if (chdir(path) == -1)
					g_xcode[0] = ((0 * l_putstr_fd_3("minishell: cd: ",
									path,
									": No such file or directory\n", 2)) + 1);
				else
					change_pwds(cmds, 0, NULL);
			}
		}
	}
	cd_with_arg(cmds);
}
	//passe a la fonction au dessus//

	/*else
		cd_with_arg(cmds);
	if (cmds->ptr_mnsh->nb_cmd != 1)
		exit(g_xcode[0]);*/