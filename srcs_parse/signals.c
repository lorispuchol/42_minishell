/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:23:15 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/06 17:37:19 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit_code_sig(void)
{	
	if (WIFEXITED(g_xcode[0]))
			g_xcode[0] = WEXITSTATUS(g_xcode[0]);
	else if (WIFSIGNALED(g_xcode[0]))
	{
		if (SIGQUIT == WTERMSIG(g_xcode[0]))
			g_xcode[0] = 131;
		else if (SIGINT == WTERMSIG(g_xcode[0]))
			g_xcode[0] = 130;
	}
}

void	ft_init_sig(void)
{
	signal(SIGINT, &ft_sigterm);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_sigterm(int code)
{
	if (code == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_xcode[1] == 0)
			rl_redisplay();
		g_xcode[0] = 1;
		signal(SIGINT, &ft_sigterm);
	}
	else if (code == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		signal(SIGQUIT, SIG_IGN);
	}
}
