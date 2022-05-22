/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:13:30 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/06 17:24:16 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_if_non_num(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		if (l_isdigit(arg[i]) != 1)
			return (1);
	return (0);
}

void	check_first(t_cmds *cmds)
{
	if (check_if_non_num(cmds->cmd[1]) == 1)
	{
		g_xcode[0] = 255;
		if (cmds->ptr_mnsh->nb_cmd == 1)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmds->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(g_xcode[0]);
	}
}

void	exit_one_valid_arg(t_cmds *cmds)
{
	unsigned char	exit_num;

	if (cmds->ptr_mnsh->nb_cmd == 1)
		ft_putstr_fd("exit\n", 2);
	exit_num = l_atoi(cmds->cmd[1]);
	exit(exit_num);
}

void	bt_exit(t_cmds *cmds)
{
	g_xcode[0] = 0;
	if (!cmds->cmd[1])
	{
		if (cmds->ptr_mnsh->nb_cmd == 1)
			ft_putstr_fd("exit\n", 2);
		exit(g_xcode[0]);
	}
	check_first(cmds);
	if (cmds->cmd[2])
	{
		g_xcode[0] = 1;
		if (cmds->ptr_mnsh->nb_cmd == 1)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		if (cmds->ptr_mnsh->nb_cmd != 1)
			exit(g_xcode[0]);
		return ;
	}
	exit_one_valid_arg(cmds);
}
