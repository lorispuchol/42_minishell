/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:07:55 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/06 17:24:16 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	bt_pwd(t_cmds *cmds)
{
	g_xcode[0] = 0;
	if (bt_outfile(cmds) == -1)
		return ;
	ft_putstr_fd(cmds->ptr_mnsh->pwd, cmds->fd_outfile);
	ft_putstr_fd("\n", cmds->fd_outfile);
	if (cmds->ptr_mnsh->nb_cmd != 1)
		exit (g_xcode[0]);
}
