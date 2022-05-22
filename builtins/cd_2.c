/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:11 by lpuchol           #+#    #+#             */
/*   Updated: 2022/05/06 19:22:37 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	bt_modif_var(int position, char *name_and_value, t_env *lst_env)
{
	t_env	*tmp;
	int		i;

	i = -1;
	tmp = lst_env;
	while (++i < position && tmp)
		tmp = tmp->next;
	if (tmp->str)
	{
		free (tmp->str);
		tmp->str = NULL;
	}
	tmp->str = l_strdup(name_and_value);
}

/* 

	=> UNUSED FUNCTION

static void	cd_with_arg(t_cmds *cmds)
{
	if (cmds->cmd[1])
	{	
		if (chdir(cmds->cmd[1]) == -1)
		{
			g_xcode[0] = 1;
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(cmds->cmd[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
			change_pwds(cmds, 0, NULL);
	}
	if (cmds->ptr_mnsh->nb_cmd != 1)
		exit(g_xcode[0]);
}*/

static int	get_position_var(char *var, t_env *lst_env)
{
	char	**var_split;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = lst_env;
	while (tmp)
	{
		var_split = l_split(tmp->str, '=');
		if (l_strcmp(var_split[0], var) == 0)
		{
			ft_free_tab(var_split);
			return (i);
		}
		tmp = tmp->next;
		ft_free_tab(var_split);
		i++;
	}
	return (-1);
}

int	l_putstr_fd_3(char *s1, char *s2, char *s3, int fd)
{
	int	count;

	count = write(fd, "minishell: ", ft_strlen("minishell: "));
	count += write(fd, s1, ft_strlen(s1));
	count += write(fd, s2, ft_strlen(s2));
	count += write(fd, s3, ft_strlen(s3));
	count += write(fd, "\n", 1);
	return (count);
}

void	change_pwds(t_cmds *cmds, int position, char *tmp)
{
	char	*pwd_value;
	char	*oldpwd_value;

	tmp = l_strdup(cmds->ptr_mnsh->pwd);
	if (cmds->ptr_mnsh->pwd)
	{
		free(cmds->ptr_mnsh->pwd);
		cmds->ptr_mnsh->pwd = NULL;
	}
	cmds->ptr_mnsh->pwd = ft_get_pwd();
	position = get_position_var("PWD", cmds->ptr_mnsh->lst_env);
	if (position != -1)
	{
		pwd_value = l_strjoin(l_strdup("PWD="), cmds->ptr_mnsh->pwd);
		bt_modif_var(position, pwd_value, cmds->ptr_mnsh->lst_env);
		free(pwd_value);
	}
	position = get_position_var("OLDPWD", cmds->ptr_mnsh->lst_env);
	if (position != -1)
	{
		oldpwd_value = l_strjoin(l_strdup("OLDPWD="), tmp);
		bt_modif_var(position, oldpwd_value, cmds->ptr_mnsh->lst_env);
		free(oldpwd_value);
	}
	free(tmp);
}
