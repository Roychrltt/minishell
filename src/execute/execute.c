/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:19:21 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/05 15:26:17 by xiaxu            ###   ########.fr       */
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

int	redirect(t_token *list, t_cmd *cmd)
{
	t_token	*temp;

	temp = list;
	while (!is_end_command(temp))
	{
		if (temp->type == REDIRECT_IN || temp->type == HEREDOC)
		{
			if (cmd->fd[0] > 0)
				close(cmd->fd[0]);
			cmd->fd[0] = open_file(temp->next->value, temp->type);
		}
		else if (temp->type == REDIRECT_OUT || temp->type == APPEND)
		{
			if (cmd->fd[1] > 1)
				close(cmd->fd[1]);
			cmd->fd[1] = open_file(temp->next->value, temp->type);
		}
		if (cmd->fd[0] == -1 || cmd->fd[1] == -1)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	execute(t_mem *mem)
{
	t_token	*temp;
	int		i;
	int		pipe_num;

	temp = mem->tokens;
	if (!expand(&temp, mem->values))
		return (0);
	i = 0;
	pipe_num = count_pipes(temp);
	while (i < pipe_num)
	{
		ft_command(temp, mem);
		while (!is_end_command(temp))
			temp = temp->next;
		temp = temp->next;
		i++;
	}
	last_child(temp, mem);
	while (i-- >= 0)
	{
		wait(NULL);
	}
	return (1);
}
