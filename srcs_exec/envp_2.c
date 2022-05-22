/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:41:34 by lpuchol           #+#    #+#             */
/*   Updated: 2022/04/26 18:45:56 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_display_lst_env(t_minishell	*mnsh)
{
	t_env	*tmp;

	if (!mnsh->lst_env)
		return ;
	tmp = mnsh->lst_env;
	while (tmp)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}

void	ft_free_tab_env(t_minishell *mnsh)
{
	if (!mnsh->tab_env)
		return ;
	free (mnsh->tab_env);
	mnsh->tab_env = NULL;
}

void	ft_free_lst_env(t_minishell *mnsh)
{
	t_env	*tmp;
	t_env	*tmp_to_free;

	if (!mnsh->lst_env)
		return ;
	tmp = mnsh->lst_env;
	while (tmp)
	{
		free(tmp->str);
		tmp->str = NULL;
		tmp = tmp->next;
	}
	tmp = mnsh->lst_env;
	while (tmp)
	{
		tmp_to_free = tmp;
		tmp = tmp->next;
		free(tmp_to_free);
		tmp_to_free = NULL;
	}
}
