/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:49:39 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/07 14:58:17 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_paths_with_cmd(char **envp, char *cmd)
{
	int		i;
	char	*str_path;
	char	**tab_paths;

	str_path = NULL;
	tab_paths = NULL;
	i = -1;
	while (envp[++i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
			&& envp[i][3] == 'H' && envp[i][4] == '=')
			str_path = (envp[i]) + 5;
	}
	if (str_path)
		tab_paths = l_split(str_path, ':');
	else
		return (NULL);
	i = -1;
	while (tab_paths[++i])
	{
		tab_paths[i] = l_strjoin(tab_paths[i], "/");
		tab_paths[i] = l_strjoin(tab_paths[i], cmd);
	}
	return (tab_paths);
}

void	ft_close_pipe(t_cmds *cmds)
{
	if (cmds->index_cmd < (cmds->ptr_mnsh->nb_cmd - 1))
		if (close((cmds)->fd_pipe[0]) == -1)
			ft_xerror(strerror(errno), "\0", "\0", 1);
}

void	ft_dup_infile(t_cmds *cmds)
{
	cmds->fd_infile = open(cmds->infile, O_RDONLY);
	if (cmds->fd_infile == -1)
		ft_xerror(cmds->infile, ": ", strerror(errno), 1);
	dup2(cmds->fd_infile, STDIN_FILENO);
	if (cmds->index_cmd != 0)
		if (close((cmds - 1)->fd_pipe[0]) == -1)
			ft_xerror(strerror(errno), "\0", "\0", 1);
	if (close(cmds->fd_infile) == -1)
		ft_xerror(strerror(errno), "\0", "\0", 1);
}

void	ft_dup_outfile(t_cmds *cmds)
{
	cmds->fd_outfile = open(cmds->outfile, O_WRONLY | O_APPEND);
	if (cmds->fd_outfile == -1)
		ft_xerror(cmds->outfile, ": ", strerror(errno), 1);
	dup2(cmds->fd_outfile, STDOUT_FILENO);
	if (close(cmds->fd_outfile) == -1)
		ft_xerror(strerror(errno), "\0", "\0", 1);
	if (cmds->index_cmd != (cmds->ptr_mnsh->nb_cmd - 1))
		if (close(cmds->fd_pipe[1]) == -1)
			ft_xerror(strerror(errno), "\0", "\0", 1);
}

void	ft_dup_pipe(t_cmds *cmds)
{
	if (cmds->infile)
		ft_dup_infile(cmds);
	else if (cmds->index_cmd != 0)
	{
		dup2((cmds - 1)->fd_pipe[0], STDIN_FILENO);
		if (close((cmds - 1)->fd_pipe[0]) == -1)
			ft_xerror(strerror(errno), "\0", "\0", 1);
	}
	if (cmds->outfile)
		ft_dup_outfile(cmds);
	else if (cmds->index_cmd < (cmds->ptr_mnsh->nb_cmd - 1))
	{
		dup2(cmds->fd_pipe[1], STDOUT_FILENO);
		if (close(cmds->fd_pipe[1]) == -1)
			ft_xerror(strerror(errno), "\0", "\0", 1);
	}
	ft_close_pipe(cmds);
}
