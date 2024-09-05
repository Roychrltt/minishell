/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:23:17 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/05 15:27:43 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_token *arg, t_mem *mem)
{
	t_token	*temp;
	int		n;

	temp = arg->next;
	n = 0;
	if (temp && !ft_strcmp(temp->value, "-n"))
		n = 1;
	if (n == 1)
		temp = temp->next;
	while (!is_end_command(temp))
	{
		if (temp->type == ARGUMENT || temp->type == SINGLEQUOTE
			|| temp->type == DOUBLEQUOTE)
		{
			if ((n && temp != arg->next->next) || (!n && temp != arg->next))
				printf(" ");
		printf("%s", temp->value);
		}
		temp = temp->next;
	}
	if (n == 0 || temp == arg->next)
		printf("\n");
	mem->exit_stat = 0;
	return (1);
}
