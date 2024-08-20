/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:24:34 by xiaxu             #+#    #+#             */
/*   Updated: 2024/08/20 17:13:27 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_tokens(char **tokens)
{
	int i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

static void	print_tokens(char **tokens)
{
	int i = 0;
	while (tokens[i])
	{
		printf("%s", tokens[i++]);
		if (tokens[i])
			printf(" ");
	}
	free_tokens(tokens);
}

int main(void)
{
	char **tokens;
	char *input = readline("test$>");
	if ((ft_strchr(input, '"') == ft_strlen(input)) && (ft_strchr(input, 39) == ft_strlen(input)))
	{
		tokens = ft_split(input, ' ');
		print_tokens(tokens);
		return (0);
	}

	int i;
	int s;
	int d;
	int status = 0;

	i = 0;
	while (input[i])
	{
		s = ft_strchr(input + i, '\'');
		d = ft_strchr(input + i, '"');
		if (status == 0 && s < d)
		{
			status = 1;
			tokens = ft_split(ft_substr(input, i, s), ' ');
			print_tokens(tokens);
			i += s;
		}
		else if (status == 0 && d < s)
		{
			status = 2;
			tokens = ft_split(ft_substr(input, i, d), ' ');
			print_tokens(tokens);
			i += d;
		}
		else if (status == 1)
		{
			printf(" ");
			while (s--)
			{
				printf("%c", input[i]);
				i++;
			}
			status = 0;
			printf(" ");
		}
		else if (status == 2)
		{
			printf(" ");
			while (d)
			{
				if (input[i] != '$')
				{
					printf("%c", input[i]);
					i++;
					d--;
				}
				else
				{
					i++;
					int x;
					int x1;
					int x2;
					x1 = ft_strchr(input + i, ' ');
					x2 = ft_strchr(input + i, '"');
					if (x1 <= x2)
						x = x1;
					else
						x = x2;
					char *to_check = ft_substr(input, i, x);
					if (!ft_strcmp(to_check, "VALUE") || !ft_strcmp(to_check, "TEST"))
						status = 3;
					i += x;
					d -= x;
					if (status == 3)
						printf("set_value");
					d--;
				}

			}
			status = 0;
			printf(" ");
		}
		else
		{
			tokens = ft_split(ft_substr(input, i, ft_strlen(input) - i), ' ');
			print_tokens(tokens);
			break;
		}
		i++;
	}
	printf("\n");
	return 0;
}
