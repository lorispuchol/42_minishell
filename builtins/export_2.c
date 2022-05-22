/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:43:13 by lpuchol           #+#    #+#             */
/*   Updated: 2022/04/30 14:35:18 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_valid_var_2(char *name)
{
	int	i;
	int	equal;

	equal = 0;
	i = 0;
	while (name[++i])
	{
		if (name[i] == '=')
			equal = 1;
		if ((l_isalpha(name[i]) != 1 && l_isdigit(name[i]) != 1
				&& name[i] != '_' && name[i] != '=') && (equal == 0))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	check_valid_var(char *name)
{
	if ((name[0] == '_' && name[1] == '\0')
		|| (name[0] == '_' && name[1] == '='))
		return (EXIT_FAILURE);
	if (l_isalpha(name[0]) != 1 && name[0] != '_')
	{
		if (name[0] == '-')
			return (EXIT_FAILURE);
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	return (check_valid_var_2(name));
}
