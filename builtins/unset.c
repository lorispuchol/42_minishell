/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:46:52 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/06 17:24:16 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static int	ft_check_valid(char *var)
{
	int	i;

	if (l_isalpha(var[0]) != 1 && var[0] != '_')
	{
		if (var[0] == '-')
			return (EXIT_FAILURE);
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (var[++i])
	{
		if (l_isalpha(var[i]) != 1 && l_isdigit(var[i]) != 1 && var[i] != '_')
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(var, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static t_env	*ft_unset_var(int position, t_env *lst_env, char *var)
{
	int		i;
	t_env	*tmp_to_free;
	t_env	*tmp;

	if (var[0] == '_' && var[1] == '\0')
		return (lst_env);
	if (position == 0)
	{
		tmp_to_free = lst_env;
		lst_env = lst_env->next;
		free(tmp_to_free->str);
		free(tmp_to_free);
		return (lst_env);
	}
	tmp = lst_env;
	i = -1;
	while ((++i < position - 1) && tmp)
		tmp = tmp->next;
	tmp_to_free = tmp->next;
	if (tmp_to_free->str[0] == '_' && tmp_to_free->str[1] == '=')
		return (lst_env);
	tmp->next = tmp->next->next;
	free(tmp_to_free->str);
	free(tmp_to_free);
	return (lst_env);
}

void	bt_unset(t_cmds *cmds)
{
	int	position;
	int	i;

	g_xcode[0] = 0;
	if (cmds->cmd[1] == NULL)
		return ;
	i = 0;
	while (cmds->cmd[++i])
	{
		if (ft_check_valid(cmds->cmd[i]) == EXIT_SUCCESS)
		{
			position = get_position_var(cmds->cmd[i], cmds->ptr_mnsh->lst_env);
			if (position > -1)
				cmds->ptr_mnsh->lst_env = ft_unset_var(position,
						cmds->ptr_mnsh->lst_env, cmds->cmd[i]);
		}
		else
			g_xcode[0] = 1;
	}	
	if (cmds->ptr_mnsh->nb_cmd != 1)
		exit(g_xcode[0]);
}
