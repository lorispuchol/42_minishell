/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:59:52 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/06 17:24:16 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	bt_outfile(t_cmds *cmds)
{
	if (ft_strlen(cmds->outfile) > 0 && cmds->ptr_mnsh->nb_cmd == 1)
	{
		cmds->fd_outfile = open(cmds->outfile, O_WRONLY | O_APPEND);
		if (cmds->fd_outfile == -1)
		{
			l_putstr_fd_3(cmds->outfile, ": ", strerror(errno), 2);
			g_xcode[0] = 1;
			return (-1);
		}
		return (cmds->fd_outfile);
	}
	cmds->fd_outfile = 1;
	return (1);
}

int	ft_check_bt_2(t_cmds *cmds)
{
	if (l_strcmp(cmds->cmd[0], "pwd") == 0)
	{
		bt_pwd(cmds);
		return (1);
	}
	if (l_strcmp(cmds->cmd[0], "echo") == 0)
	{
		bt_echo(cmds);
		return (1);
	}
	if (l_strcmp(cmds->cmd[0], "exit") == 0)
	{
		bt_exit(cmds);
		return (1);
	}
	if (l_strcmp(cmds->cmd[0], "cd") == 0)
	{
		bt_cd(cmds);
		return (1);
	}
	return (0);
}

int	ft_check_bt(t_cmds *cmds)
{
	if (!cmds->cmd[0] && cmds->ptr_mnsh->nb_cmd != 1)
		exit (0);
	if (!cmds->cmd[0] && cmds->ptr_mnsh->nb_cmd == 1)
		return (0);
	if (l_strcmp(cmds->cmd[0], "export") == 0)
	{
		bt_export(cmds, 0, 0, NULL);
		return (1);
	}
	if (l_strcmp(cmds->cmd[0], "env") == 0)
	{
		bt_env_only(cmds);
		return (1);
	}
	if (l_strcmp(cmds->cmd[0], "unset") == 0)
	{
		bt_unset(cmds);
		return (1);
	}
	return (ft_check_bt_2(cmds));
}
