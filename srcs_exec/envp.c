/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:10:52 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/04 07:19:41 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_convert_env_in_tab(t_minishell *mnsh)
{
	int		i;
	t_env	*tmp;

	tmp = mnsh->lst_env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if (!i)
		return ;
	mnsh->tab_env = ft_xmalloc(sizeof(char *) * (i + 1));
	mnsh->tab_env[i] = NULL;
	tmp = mnsh->lst_env;
	i = 0;
	while (tmp)
	{
		mnsh->tab_env[i] = tmp->str;
		tmp = tmp->next;
		i++;
	}
}

char	*ft_increment_shlvl(char *str_shlvl, int i)
{
	int		i_lvl;
	char	*a_lvl;
	char	*str;

	i = 0;
	while (str_shlvl[i] && str_shlvl[i] != '=')
		i++;
	if (!str_shlvl[i + 1])
	{
		str = l_strdup("SHLVL=1");
		return (str);
	}
	i_lvl = l_atoi((str_shlvl + i + 1));
	i_lvl++;
	a_lvl = l_itoa(i_lvl);
	str = l_strjoin(l_strdup("SHLVL="), a_lvl);
	free(a_lvl);
	return (str);
}

static int	check_if_var(char *var, t_env *lst_env)
{
	t_env	*tmp;

	tmp = lst_env;
	while (tmp)
	{
		if (l_strncmp(var, tmp->str, ft_strlen(var)) == 0)
			return (EXIT_SUCCESS);
		tmp = tmp->next;
	}
	return (EXIT_FAILURE);
}

void	set_mandatory_var(t_env *tmp, t_env *lst_env, t_minishell *mnsh)
{
	if (check_if_var("PWD=", lst_env) == EXIT_FAILURE)
	{
		tmp->next = ft_xmalloc(sizeof(t_env));
		tmp->next->str = l_strjoin(l_strdup("PWD="), mnsh->pwd);
		tmp = tmp->next;
		tmp->next = NULL;
	}
	if (check_if_var("SHLVL=", lst_env) == EXIT_FAILURE)
	{
		tmp->next = ft_xmalloc(sizeof(t_env));
		tmp->next->str = l_strdup("SHLVL=1");
		tmp = tmp->next;
		tmp->next = NULL;
	}
	set_mandatory_var_2(tmp, lst_env);
}

t_env	*ft_get_env(char **envp, t_minishell *mnsh, int i)
{
	t_env	*lst_env;
	t_env	*tmp;

	if (!envp[0])
		return (l_no_env_at_launch(mnsh));
	lst_env = ft_xmalloc(sizeof(t_env));
	tmp = lst_env;
	while (envp[++i])
	{
		if (l_strncmp("OLDPWD=", envp[i], 7) != 0)
		{
			if (l_strncmp("SHLVL=", envp[i], 6) == 0)
				tmp->str = ft_increment_shlvl(envp[i], 0);
			else
				tmp->str = l_strdup(envp[i]);
			if (envp[i + 1])
			{
				tmp->next = ft_xmalloc(sizeof(t_env));
				tmp = tmp->next;
			}
		}
	}
	tmp->next = NULL;
	set_mandatory_var(tmp, lst_env, mnsh);
	return (lst_env);
}
