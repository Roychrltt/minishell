/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:40:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/23 15:26:56 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	g_pid = 0;
int	add_env(char *s, t_env *env)
{}

static t_env	*copy_env(char **envp)
{
	t_env	*list;
	t_env	*temp;
	int		i;

	i = 0;
	list = malloc(sizeof (t_env));
	if (!list)
		return (NULL);
	while (envp[i])
	{
		temp = list;
		add_env(envp[i], temp);
		i++;
	}
	return (list);
}

int	main(int argc, char **argv, char **envp)
{
	t_mem	*mem;

	(void)argc, (void)argv;
	char	*input;
	char	**tokens;
	//mem = init_mem();
	mem->env = copy_env(envp);
	sig_init_signals();
	while (1)
	{
		input = readline("minishell$>");
		if (!input || !ft_strcmp(input, "exit"))
		{
			if (!input)
				printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		tokens = ft_split(input, ' ');
		if (is_builtins(tokens[0]))
			do_builtins(tokens[0], mem, tokens);
		free(input);
	}
	rl_clear_history();
	return (0);
}
