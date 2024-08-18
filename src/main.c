/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:40:25 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/15 15:49:21 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_pid = 0;

int	main()
{
	char *input;

	while((input = readline("minishell> ")) != NULL) {
		add_history(input);

		printf("You entered: %s\n", input);

		free(input);
	}
	return (0);
}
