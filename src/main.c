/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:40:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/27 16:37:35 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	g_pid = 0;

static t_env	*copy_env(char **envp)
{
	t_env	*list;
	t_env	*temp;
	int		i;

	list = NULL;
	temp = NULL;
	i = 0;
	while (envp[i])
	{
		temp = add_env(envp[i], &list);
		if (!list)
			list = temp;
		i++;
	}
	return (list);
}

static int	init_mem(t_mem *mem, char **envp)
{
	mem->exit_stat = 0;
	mem->values = copy_env(envp);
	mem->my_env = env_dup(envp);
	return (0);
}

static int	init_var(t_var *var, char **envp)
{
	(void)envp;
	var->squote = 0;
	var->dquote = 0;
	var->word = 0;
	var->tokens = tokenizer(var->input, var);
	if (!var->tokens)
		free(var->input);
//	var->count = count_token(var->input, var);
//	handle_signals();
//	recup_env(var, env);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_var	var;
	t_mem	mem;

	(void)argc;
	if (!getenv("PATH"))
		return (0);
	sig_init_signals();
	var.argv = argv;
	var.found = 0;
	init_mem(&mem, envp);
	while (1)
	{
		var.input = readline("minishell$>");
		init_var(&var, envp);
		mem.input = var.input;
		if (!var.input || !ft_strcmp(var.input, "exit"))
		{
			printf("exit\n");
			break;
		}
		if (*(var.input))
			add_history(var.input);
		mem.tokens = ft_split(var.input, ' ');
		mem.token = parsing(var.tokens);
		mem.cmds = parsing();
		if (is_builtins(mem.tokens[0]))
			do_builtins(mem.tokens[0], &mem, mem.tokens);
		free(input);
		free_tab(mem.tokens);
	}
	rl_clear_history();
	return (0);
}
