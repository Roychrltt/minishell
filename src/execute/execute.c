/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:19:21 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/01 21:13:26 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_pipes(t_token *list)
{
	int		num;
	t_token	*temp;

	num = 0;
	temp = list;
	while (temp)
	{
		if (!ft_strcmp(temp->value, "|"))
			num++;
		temp = temp->next;
	}
	return (num);
}

int	execute(t_mem *mem)
{
	t_token	*temp;
	int		pipe_num;

	temp = mem->tokens;
	pipe_num = count_pipes(temp);
	(void)pipe_num;
	if (!expand(&temp, mem->values))
		return (0);
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
/*
int	redirect(t_token *list, t_cmd *cmd)
{
	t_token	*temp;

	temp = list;
	cmd->fd_in = -2;
	cmd->fd_out = -2;
	while (!is_end_command(temp))
	{
		if (temp->type == REDICET_IN || temp->type == HERE_DOC)
		{
			if (cmd->fd_in > 0)
				close(cmd->fd_in);
			cmd->fd_in = open_file(temp->next->value, temp->type);
		}
		if (temp->type == REDICET_OUT || temp->type == APPEND)
		{
			if (cmd->fd_out > 0)
				close(cmd->fd_out);
			cmd->fd_out = open_file(temp->next->value, temp->type);
		}
		if ((cmd->fd_in < 0 && cmd->fd_in != -2) ||
			(cmd->fd_out < 0 && cmd->fd_out != -2))
			return (0);
		temp = temp->next;
	}
	return (1);
}*/
