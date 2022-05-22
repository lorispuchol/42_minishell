/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvergobb <dvergobb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:29:06 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/04 07:19:29 by dvergobb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*l_no_env_at_launch(t_minishell *mnsh)
{
	t_env	*lst_env;
	t_env	*tmp;

	lst_env = ft_xmalloc(sizeof(t_env));
	tmp = lst_env;
	tmp->str = l_strdup("SHLVL=1");
	tmp->next = NULL;
	set_mandatory_var(tmp, lst_env, mnsh);
	return (lst_env);
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

void	set_mandatory_var_2(t_env *tmp, t_env *lst_env)
{
	if (check_if_var("_=", lst_env) == EXIT_FAILURE)
	{
		tmp->next = ft_xmalloc(sizeof(t_env));
		tmp->next->str = l_strjoin(l_strdup("_="),
				"/Users/lpuchol/Documents/minishell_gh/env");
		tmp = tmp->next;
		tmp->next = NULL;
	}
	if (check_if_var("OLDPWD\0", lst_env) == EXIT_FAILURE)
	{
		tmp->next = ft_xmalloc(sizeof(t_env));
		tmp->next->str = l_strdup("OLDPWD\0");
		tmp->next->next = NULL;
	}
}
