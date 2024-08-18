/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:48:44 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/18 16:17:21 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(char **s, t_mem *mem)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (s[1] && !ft_strcmp(s[1], "-n"))
		n = 1;
	if (n)
		i++;
	while (s[i])
	{
		if ((n && i > 2) || (!n && i > 1))
			printf(" ");
		printf("%s", s[i]);
		i++;
	}
	if (!n || i == 1)
		printf("\n");
	mem->exit_stat = 0;
	return (1);
}
