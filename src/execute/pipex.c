/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:41:50 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/03 00:44:53 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_args(t_token *list)
{
	t_token	*temp;
	int		i;

	temp = list;
	i = 0;
	while (!is_end_command(temp))
	{
		if (temp->type == ARGUMENT || temp->type == SINGLEQUOTE
			|| temp->type == DOUBLEQUOTE)
			i++;
		temp = temp->next;
	}
	return (i);
}

int	exec_command(t_cmd *cmd, t_token *list, t_mem *mem)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = list;
	cmd->count = count_args(list);
	cmd->args = malloc(sizeof(char *) * (cmd->count + 2));
	while (!is_end_command(temp))
	{
		if (temp->type == ARGUMENT || temp->type == SINGLEQUOTE
			|| temp->type == DOUBLEQUOTE || temp->type == COMMAND)
		{
			cmd->args[i] = ft_strdup(temp->value);
			if (!cmd->args[i])
				return (free_tab(cmd->args), 0);
			i++;
		}
		temp = temp->next;
	}
	cmd->args[i] = NULL;
	cmd->command = get_command(mem->paths, list->value);
	execve(cmd->command, cmd->args, mem->envp);
	perror("execve failure");
	return (0);
}

void	ft_child(t_token *list, t_mem *mem)
{
	t_cmd	cmd;
	pid_t	pid;

	if (pipe(cmd.fd) == -1)
		perror("Pipe error");
	redirect(list, &cmd);
	while (list->type != COMMAND)
		list = list->next;
	pid = fork();
	if (pid < 0)
		perror("Fork error");
	if (pid == 0)
	{
		close(cmd.fd[0]);
		dup2(cmd.fd[1], STDOUT_FILENO);
		close(cmd.fd[1]);
		exec_command(&cmd, list, mem);
	}
	else
	{
		close(cmd.fd[1]);
		dup2(cmd.fd[0], STDIN_FILENO);
		close(cmd.fd[0]);
	}
}

void	last_child(t_token *list, t_mem *mem)
{
	t_cmd	cmd;
	pid_t	pid;

	redirect(list, &cmd);
	while (list->type != COMMAND)
		list = list->next;
	pid = fork();
	if (pid < 0)
		perror("Fork error");
	if (pid == 0)
	{
		dup2(cmd.fd[1], STDOUT_FILENO);
		close(cmd.fd[1]);
		exec_command(&cmd, list, mem);
	}
	close(cmd.fd[1]);
}
/*
int	pipex(int count, char **tokens, char **envp)
{
	int		i;
	int		infile;
	int		outfile;

	if (!ft_strcmp(tokens[0], "<<"))
	{
		if (argc < 6)
			exit_handler_here_doc();
		i = 3;
		infile = get_here_doc_input(tokens);
	}
	else
	{
		i = 2;
		infile = open_file(argv[1], 0);
	}
	outfile = open_file(argv[argc - 1], 1);
	dup2(infile, STDIN_FILENO);
	close(infile);
	while (i < argc - 2)
		ft_pipe(argv[i++], envp);
	last_child(outfile, argc, argv, envp);
	result_handler(argc);
}*/
