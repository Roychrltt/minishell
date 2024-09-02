/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:19:21 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/02 22:50:48 by xiaxu            ###   ########.fr       */
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
	cmd->fd[0] = -2;
	cmd->fd[1] = -2;
	while (!is_end_command(temp))
	{
		if (temp->type == REDIRECT_IN || temp->type == HEREDOC)
		{
			if (cmd->fd[0] > 0)
				close(cmd->fd[0]);
			cmd->fd[0] = open_file(temp->next->value, temp->type);
		}
		if (temp->type == REDIRECT_OUT || temp->type == APPEND)
		{
			if (cmd->fd[1] > 0)
				close(cmd->fd[1]);
			cmd->fd[1] = open_file(temp->next->value, temp->type);
		}
		if ((cmd->fd[0] < 0 && cmd->fd[0] != -2) ||
			(cmd->fd[1] < 0 && cmd->fd[1] != -2))
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
	i = 0;
	pipe_num = count_pipes(temp);
	if (!expand(&temp, mem->values))
		return (0);
	while (i < pipe_num)
	{
		ft_child(&temp, mem);
		temp = temp->next;
		i++;
	}
	last_child(&temp, mem);
	return (1);
}
