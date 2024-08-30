/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:19:21 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/30 23:12:37 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute(t_mem *mem)
{
	t_token	*temp;

	temp = mem->tokens;
	while (!is_end_command(temp))
	{
		if (temp->type == COMMAND)
			break ;
		temp = temp->next;
	}
	if (is_builtins(temp->value))
		do_builtins(temp, mem);
	return (1);
}
