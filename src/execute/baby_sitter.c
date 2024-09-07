/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   baby_sitter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:46:20 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/07 14:47:58 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect(t_cmd *cmd)
{
	if (cmd->infile > STDIN_FILENO)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (cmd->outfile > STDOUT_FILENO)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
}

static void	execute_builtins(t_token *list, t_cmd *cmd, t_mem *mem)
{
	do_builtins(list, mem);
	free(cmd->command);
	free_tab(cmd->args);
	exit(0);
}

void	do_command(t_token *list, t_cmd *cmd, t_mem *mem, int status)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("Fork error");
	if (pid == 0)
	{
		if (status == 1)
		{
			close(cmd->fd[0]);
			if (cmd->outfile <= STDOUT_FILENO)
			{
				dup2(cmd->fd[1], STDOUT_FILENO);
				close(cmd->fd[1]);
			}
			else
				close(cmd->fd[1]);
		}
		if (is_builtins(cmd->command))
			execute_builtins(list, cmd, mem);
		else
			execve(cmd->command, cmd->args, mem->envp);
	}
}
