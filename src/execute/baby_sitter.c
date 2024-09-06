/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   baby_sitter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:46:20 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/06 18:58:36 by xiaxu            ###   ########.fr       */
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

void	do_command(t_cmd *cmd, t_mem *mem, int status)
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
		}
		execve(cmd->command, cmd->args, mem->envp);
	}
}
