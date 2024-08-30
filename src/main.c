/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:40:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/31 00:01:36 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	g_pid = 0;

static int	init_mem(t_mem *mem)
{
	if (!check_quotes(mem->input))
		return (free(mem->input), 0);
	mem->found = 0;
	mem->squote = 0;
	mem->dquote = 0;
	mem->word = 0;
	mem->count = count_token(mem->input, mem);
	mem->args = tokenizer(mem->input, mem);
//	mem->paths = get_paths(envp);
	return (1);
}

static void	free_mem(t_mem *mem)
{
	free(mem->input);
	free_tab(mem->args);
	free_tokens(mem->tokens);
}

int	main(int argc, char **argv, char **envp)
{
	t_mem	mem;

	(void)argc;
	sig_init_signals();
	mem.argv = argv;
	mem.exit_stat = 0;
	mem.values = sort_env(envp);
	mem.my_env = env_dup(envp);
	while (1)
	{
		mem.input = readline("minishell$>");
		if (!mem.input || !ft_strcmp(mem.input, "exit"))
		{
			free(mem.input);
			printf("exit\n");
			break ;
		}
		if (!init_mem(&mem))
			continue ;
		if (*(mem.input))
			add_history(mem.input);
		mem.tokens = tokens_to_list(mem.args);
		if (mem.tokens)
			execute(&mem);
		free_mem(&mem);
	}
	free_env(mem.values);
	free_env(mem.my_env);
	rl_clear_history();
	return (0);
}
