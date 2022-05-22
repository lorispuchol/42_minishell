/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:03:04 by lpuchol           #+#    #+#             */
/*   Updated: 2022/04/26 17:49:16 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_pwd(void)
{
	int		size;
	char	*pwd;
	char	*tmp;

	pwd = NULL;
	size = 5;
	while (pwd == NULL)
	{
		pwd = ft_xmalloc(sizeof(char) * size);
		tmp = pwd;
		pwd = getcwd(pwd, size);
		if (!pwd)
		{
			free(tmp);
			size += 5;
		}
	}
	return (pwd);
}
