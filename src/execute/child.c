/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:41:50 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/08 01:02:18 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_fds(t_token *list, t_cmd *cmd)
{
	t_token	*temp;

	temp = list;
	while (!is_end_command(temp))
	{
		if (temp->type == REDIRECT_IN || temp->type == HEREDOC)
		{
			if (cmd->infile > 0)
				close(cmd->infile);
			cmd->infile = open_file(temp->next->value, temp->type);
			if (temp->type == HEREDOC)
				cmd->heredoc = 1;
		}
		else if (temp->type == REDIRECT_OUT || temp->type == APPEND)
		{
			if (cmd->outfile > 1)
				close(cmd->outfile);
			cmd->outfile = open_file(temp->next->value, temp->type);
		}
		if (cmd->infile == -1 || cmd->outfile == -1)
			return (0);
		temp = temp->next;
	}
	return (1);
}

static int	init_cmd(t_cmd *cmd, t_token *list, t_mem *mem)
{
	cmd->infile = -2;
	cmd->outfile = -2;
	cmd->heredoc = 0;
	if (!get_fds(list, cmd))
		return (0);
	cmd->count = count_args(list);
	cmd->args = malloc(sizeof(char *) * (cmd->count + 2));
	if (!cmd->args)
		return (0);
	if (!get_args(&(cmd->args), list))
		return (0);
	while (!is_end_command(list) && list->type != COMMAND)
		list = list->next;
	if (is_end_command(list))
		return (0);
	cmd->command = get_command(mem->paths, list->value);
	if (!cmd->command)
		return (0);
	return (1);
}

int	ft_command(t_token *list, t_mem *mem)
{
	t_cmd	cmd;

	if (pipe(cmd.fd) == -1)
		perror("Pipe error");
	if (!init_cmd(&cmd, list, mem))
		return (0);
	do_command(list, &cmd, mem, 1);
	if (cmd.infile > STDIN_FILENO)
		close(cmd.infile);
	if (cmd.outfile > STDOUT_FILENO)
		close(cmd.outfile);
	close(cmd.fd[1]);
	dup2(cmd.fd[0], STDIN_FILENO);
	close(cmd.fd[0]);
	free_tab(cmd.args);
	free(cmd.command);
	if (cmd.heredoc)
		unlink(".here_doc.tmp");
	return (1);
}

int	last_child(t_token *list, t_mem *mem)
{
	t_cmd	cmd;

	if (!init_cmd(&cmd, list, mem))
		return (0);
	redirect(&cmd);
	if (is_builtins(cmd.command))
		do_builtins(list, mem);
	else
		do_command(list, &cmd, mem, 0);
	if (cmd.infile > STDIN_FILENO)
		close(cmd.infile);
	if (cmd.outfile > STDOUT_FILENO)
		close(cmd.outfile);
	dup2(mem->saved_stdin, STDIN_FILENO);
	dup2(mem->saved_stdout, STDOUT_FILENO);
	free_tab(cmd.args);
	free(cmd.command);
	if (cmd.heredoc)
		unlink(".here_doc.tmp");
	return (1);
}
