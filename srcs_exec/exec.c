/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:57:29 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/07 15:08:03 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_bad_cmd(t_cmds *cmds)
{
	if (l_strncmp("Exec format error", strerror(errno),
			ft_strlen("Exec format error")) == 0)
		exit (0);
	if ((cmds->cmd[0][0] == '.' || cmds->cmd[0][0] == '/' ||
		cmds->cmd[0][ft_strlen(cmds->cmd[0]) - 1] == '/')
			&& (l_strncmp("Permission denied", strerror(errno),
				ft_strlen("Permission denied")) == 0))
		ft_xerror(cmds->cmd[0], ": ", strerror(errno), 126);
	if (cmds->cmd[0][0] == '.' || cmds->cmd[0][0] == '/' ||
			cmds->cmd[0][ft_strlen(cmds->cmd[0]) - 1] == '/')
		ft_xerror(cmds->cmd[0], ": ", strerror(errno), 127);
	ft_xerror(cmds->cmd[0], ": ", "command not found", 127);
}

void	ft_exec_child(t_cmds *cmds)
{
	char	**path_and_cmd;
	int		i;

	i = 1;
	if (!cmds->cmd[0])
		exit(0);
	ft_dup_pipe(cmds);
	ft_check_bt(cmds);
	if (access(cmds->cmd[0], X_OK) == 0)
		execve(cmds->cmd[0], cmds->cmd, cmds->ptr_mnsh->tab_env);
	if (cmds->cmd[0][0] == '.' || cmds->cmd[0][0] == '/')
		ft_bad_cmd(cmds);
	path_and_cmd = get_paths_with_cmd(cmds->ptr_mnsh->tab_env, cmds->cmd[0]);
	if (path_and_cmd == NULL)
		ft_bad_cmd(cmds);
	i = -1;
	while (path_and_cmd[++i] && path_and_cmd)
		if (access(path_and_cmd[i], X_OK) == 0)
			execve(path_and_cmd[i], cmds->cmd, cmds->ptr_mnsh->tab_env);
	ft_bad_cmd(cmds);
}

static void	ft_fork_ps_2(int i, t_minishell *mnsh)
{
	if (mnsh->id_fork[i] == 0)
		ft_exec_child(&mnsh->cmds[i]);
	if (i < mnsh->nb_cmd - 1)
		if (close(mnsh->cmds[i].fd_pipe[1]) == -1)
			ft_xerror(strerror(errno), "\0", "\0", 1);
	if (i > 0)
		if (close(mnsh->cmds[i - 1].fd_pipe[0]) == -1)
			ft_xerror(strerror(errno), "\0", "\0", 1);
}

int	ft_fork_ps(t_minishell *mnsh)
{
	int	i;

	mnsh->id_fork = ft_xmalloc(sizeof(pid_t) * mnsh->nb_cmd);
	i = -1;
	g_xcode[0] = 0;
	while (++i < mnsh->nb_cmd)
	{
		if (i < mnsh->nb_cmd - 1)
			if (pipe(mnsh->cmds[i].fd_pipe) == -1)
				ft_xerror(strerror(errno), "\0", "\0", 1);
		mnsh->id_fork[i] = fork();
		signal(SIGQUIT, &ft_sigterm);
		if (mnsh->id_fork[i] == -1)
		{
			ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n",
				2);
			g_xcode[0] = 1;
			return (-1);
		}
		ft_fork_ps_2(i, mnsh);
	}
	return (1);
}

void	ft_exec(t_minishell *mnsh)
{
	int	i;
	int	builtin;
	int	test_fork;

	test_fork = 0;
	builtin = 0;
	if (mnsh->nb_cmd == 1)
		builtin = ft_check_bt(&mnsh->cmds[0]);
	if (builtin == 1)
		return ;
	if (ft_fork_ps(mnsh) == -1)
		test_fork = 1;
	i = -1;
	while (++i < mnsh->nb_cmd)
		waitpid(mnsh->id_fork[i], &g_xcode[0], 0);
	ft_exit_code_sig();
	signal(SIGQUIT, SIG_IGN);
	if (test_fork == 1)
		g_xcode[0] = 1;
}

/*
	dprintf(2, "||||||DEBUT|||||||\n");
	dprintf(2, "nb cmds: %d\n\n", mnsh->nb_cmd);

	i = -1;
	int	j = -1;
	while (++i < mnsh->nb_cmd)
	{
		while(mnsh->cmds[i].cmd[++j])
		{
			dprintf(2, "%s\n", mnsh->cmds[i].cmd[j]);
			dprintf(2, "-------\n");
		}
			dprintf(2, "=================\n\n");
		j = -1;
	}
	dprintf(2, "||||||FIN|||||||\n\n");
	// return ;
		signal(SIGQUIT, &ft_sigterm);
*/