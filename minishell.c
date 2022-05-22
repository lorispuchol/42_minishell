/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:44:24 by dvergobb          #+#    #+#             */
/*   Updated: 2022/05/06 19:27:55 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	ft_readline_ext(t_minishell *minishell, int i)
{
	ft_exec(minishell);
	g_xcode[1] = 0;
	while (++i < minishell->nb_cmd)
		ft_free_tab(minishell->cmds[i].cmd);
	if (minishell->cmds->infile != NULL)
	{
		free(minishell->cmds->infile);
		minishell->cmds->infile = NULL;
	}
	if (minishell->cmds->outfile != NULL)
	{
		free(minishell->cmds->outfile);
		minishell->cmds->outfile = NULL;
	}
	if (minishell->cmds)
	{
		free(minishell->cmds);
		minishell->cmds = NULL;
	}
	if (minishell->id_fork)
	{
		free(minishell->id_fork);
		minishell->id_fork = NULL;
	}
}

static void	ft_readline(t_minishell *minishell)
{
	char	*input;

	while (1)
	{
		input = NULL;
		ft_convert_env_in_tab(minishell);
		input = readline("minishell$ ");
		if (input == NULL)
		{
			printf("minishell: exit\n");
			exit(EXIT_SUCCESS);
		}
		g_xcode[1] = 1;
		add_history(input);
		if (ft_strlen(input) > 0)
		{
			if (ft_parse(input, minishell) == EXIT_SUCCESS)
				ft_readline_ext(minishell, -1);
		}
		else
			g_xcode[0] = 127;
		ft_free_tab_env(minishell);
		free(input);
	}
}

static void	ft_init_struct(char **envp, t_minishell *mnsh)
{
	mnsh->pipe = 0;
	g_xcode[0] = 0;
	g_xcode[1] = 0;
	mnsh->tab_env = NULL;
	mnsh->id_fork = NULL;
	mnsh->pwd = ft_get_pwd();
	mnsh->cmds = NULL;
	mnsh->lst_env = NULL;
	mnsh->lst_env = ft_get_env(envp, mnsh, -1);
}

static void	ft_launch_minishell(char **envp, t_minishell *mnsh)
{
	ft_init_sig();
	ft_init_struct(envp, mnsh);
	ft_readline(mnsh);
	if (mnsh)
	{
		free(mnsh);
		mnsh = NULL;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		return (EXIT_FAILURE);
	if (ac != 1)
		return (ft_putstr_fd("No arguments are allowed for this project\n", 2));
	(void)av;
	ft_launch_minishell(envp, minishell);
	return (0);
}
