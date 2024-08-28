/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:40:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/28 15:20:25 by xiaxu            ###   ########.fr       */
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

static int	init_var(t_var *var, char **argv, char **envp)
{
	(void)envp;
	var->found = 0;
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
	sig_init_signals();
	init_var(&var, argv, envp); // got char **tokens here
	init_mem(&mem, envp);
	while (1)
	{
		var.input = readline("minishell$>");
		mem.input = var.input;
		if (!var.input || !ft_strcmp(var.input, "exit"))
		{
			printf("exit\n");
			break;
		}
		if (*(var.input))
			add_history(var.input);
		mem.tokens = tokens_to_list(var.tokens);
		if (mem.tokens)
			execute(var, mem);
		free(var.input);
		free_tab(var.tokens);
		free_tokens(mem.tokens);
	}
	rl_clear_history();
	return (0);
}
