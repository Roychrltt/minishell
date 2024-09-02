/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:19:21 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/03 00:31:25 by xiaxu            ###   ########.fr       */
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
	cmd->fd[0] = 0;
	cmd->fd[1] = 1;
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

static int	childfree(t_token *list, t_mem *mem)
{
	t_cmd	cmd;

	if (!redirect(list, &cmd))
		return (0);
	if (cmd.fd[0] == -2)
		cmd.fd[0] = STDIN_FILENO;
	if (cmd.fd[1] == -2)
		cmd.fd[1] = STDOUT_FILENO;
	while (list->type != COMMAND)
		list = list->next;
	if (is_builtins(list->value))
		return (do_builtins(list, mem));
	exec_command(&cmd, list, mem);
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
	if (pipe_num == 0)
		return (childfree(temp, mem));
	while (i < pipe_num)
	{
		ft_child(temp, mem);
		while (!is_end_command(temp))
			temp = temp->next;
		temp = temp->next;
		i++;
	}
	last_child(temp, mem);
	return (1);
}
