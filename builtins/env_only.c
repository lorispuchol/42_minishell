/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_only.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:32:35 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/06 17:24:16 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	bt_env_only(t_cmds *cmds)
{
	t_env	*tmp;

	g_xcode[0] = 0;
	if (bt_outfile(cmds) == -1)
		return ;
	tmp = cmds->ptr_mnsh->lst_env;
	while (tmp)
	{
		if (l_strchr(tmp->str, '=') == 1)
		{
			ft_putstr_fd(tmp->str, cmds->fd_outfile);
			ft_putstr_fd("\n", cmds->fd_outfile);
		}
		tmp = tmp->next;
	}
	if (cmds->ptr_mnsh->nb_cmd != 1)
		exit (g_xcode[0]);
}
