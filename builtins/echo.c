/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:40:38 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/06 17:24:16 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_option(char *str_opt)
{
	int	i;

	if (str_opt[0] != '-')
		return (-1);
	if (str_opt[1] != 'n')
		return (-1);
	i = 1;
	while (str_opt[++i])
		if (str_opt[i] != 'n')
			return (-1);
	return (1);
}

void	bt_echo(t_cmds *cmds)
{
	int	i;
	int	opt_n;

	if (bt_outfile(cmds) == -1)
		return ;
	opt_n = 0;
	i = 0;
	while (cmds->cmd[++i] && check_option(cmds->cmd[i]) == 1)
		opt_n = 1;
	while (cmds->cmd[i])
	{
		ft_putstr_fd(cmds->cmd[i], cmds->fd_outfile);
		if (cmds->cmd[i + 1])
			ft_putstr_fd(" ", cmds->fd_outfile);
		i++;
	}
	if (opt_n != 1)
		ft_putstr_fd("\n", cmds->fd_outfile);
	g_xcode[0] = 0;
	if (cmds->ptr_mnsh->nb_cmd != 1)
		exit(g_xcode[0]);
}
