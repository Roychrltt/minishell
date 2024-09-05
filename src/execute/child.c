/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:41:50 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/05 23:19:58 by xiaxu            ###   ########.fr       */
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

static int	get_args(char ***args, t_token *list)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = list;
	while (!is_end_command(temp))
	{
		if (temp->type == ARGUMENT || temp->type == SINGLEQUOTE
			|| temp->type == DOUBLEQUOTE || temp->type == COMMAND)
		{
			(*args)[i] = ft_strdup(temp->value);
			if (!(*args)[i])
				return (free_tab(*args), 0);
			i++;
		}
		temp = temp->next;
	}
	(*args)[i] = NULL;
	return (1);
}

static int	init_cmd(t_cmd *cmd, t_token *list, t_mem *mem)
{
	if (!redirect(list, cmd))
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
	pid_t	pid;

	if (pipe(cmd.fd) == -1)
		perror("Pipe error");
	if (!init_cmd(&cmd, list, mem))
		return (0);
	pid = fork();
	if (pid < 0)
		perror("Fork error");
	if (pid == 0)
	{
		close(cmd.fd[0]);
		dup2(cmd.fd[1], STDOUT_FILENO);
		close(cmd.fd[1]);
		if (!is_builtins(cmd.command))
			execve(cmd.command, cmd.args, mem->envp);
		else
		{
			do_builtins(list, mem);
			free_tab(cmd.args);
			free(cmd.command);
		}
		exit(0);
	}
	else
	{
		close(cmd.fd[1]);
		dup2(cmd.fd[0], STDIN_FILENO);
		close(cmd.fd[0]);
	}
	return (1);
}

int	last_child(t_token *list, t_mem *mem)
{
	t_cmd	cmd;
	pid_t	pid;

	cmd.fd[0] = STDIN_FILENO;
	cmd.fd[1] = STDOUT_FILENO;
	if (!init_cmd(&cmd, list, mem))
		return (0);
	pid = fork();
	if (pid < 0)
		perror("Fork error");
	if (pid == 0)
	{
		dup2(cmd.fd[1], STDOUT_FILENO);
		if (cmd.fd[1] != STDOUT_FILENO)
			close(cmd.fd[1]);
		if (!is_builtins(cmd.command))
			execve(cmd.command, cmd.args, mem->envp);
		else
		{
			do_builtins(list, mem);
			free_tab(cmd.args);
			free(cmd.command);
			return (1);
		}
	}
	if (cmd.fd[1] != STDOUT_FILENO)
		close(cmd.fd[1]);
	fprintf(stderr, "cmd.fd[0]: %d, cmd.fd[1]: %d\n", cmd.fd[0], cmd.fd[1]);
	dup2(mem->saved_stdin, STDIN_FILENO);
	dup2(mem->saved_stdout, STDOUT_FILENO);
	//close(mem->saved_stdin);
	//close(mem->saved_stdout);
	return (1);
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
