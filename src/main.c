/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:40:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/19 16:45:31 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

// void rl_clear_history(void);
// int rl_on_new_line(void);
// int rl_replace_line(const char *text, int clear_undo);
// void rl_redisplay(void);
// void add_history(const char *line)
int	g_pid = 0;

static void	sigint_handler(int signum) {
	(void)signum; // Unused parameter
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigquit_handler(int signum) {
	(void)signum;
	// Ignore SIGQUIT
	printf("\b\b  \b\b");
	rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char	*input;
	char	**tokens;
	t_mem	mem;

	// Set up signal handler for SIGINT
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
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
			do_builtins(tokens[0], &mem, tokens, envp);
		free(input);
	}
	rl_clear_history();
	return (0);
}
