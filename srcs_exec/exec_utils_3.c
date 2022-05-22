/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:53:34 by lpuchol           #+#    #+#             */
/*   Updated: 2022/04/26 18:07:18 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	l_isdigit(int a)
{
	int	ret;

	ret = 0;
	if (a >= '0' && a <= '9')
		ret = 1;
	return (ret);
}

int	l_isalpha(int a)
{
	int	ret;

	ret = 0;
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		ret = 1;
	return (ret);
}

void	*l_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = ft_xmalloc(count * size);
	while (i < (count * size))
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}
