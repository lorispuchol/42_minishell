/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpuchol <lpuchol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:51:06 by lpuchol           #+#    #+#             */
/*   Updated: 2022/04/15 19:14:12 by lpuchol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_xerror(char *s1, char *sp1, char *s2, int nb_exit)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(sp1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
	exit (nb_exit);
}

void	*ft_xmalloc(size_t size)
{
	void	*address;

	address = malloc(size);
	if (!address)
		ft_xerror(strerror(errno), "\0", "\0", 1);
	return (address);
}

void	ft_display_tab(char **tabl)
{
	int	i;

	if (!tabl)
		return ;
	i = -1;
	while (tabl[++i])
		printf ("%s\n", tabl[i]);
}

char	*l_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i1;
	int		i2;

	i1 = -1;
	i2 = -1;
	if (!s2)
		return ((char *)s1);
	if (!s1)
		return (l_strdup(s2));
	str = (char *)l_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (str == NULL)
		return (NULL);
	while (s1[++i1])
		str[i1] = s1[i1];
	while (s2[++i2])
		str[i1++] = s2[i2];
	str[i1] = '\0';
	free((void *)s1);
	s1 = NULL;
	return (str);
}
