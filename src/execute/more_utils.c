/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:35:18 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/06 15:14:37 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_args(t_token *list)
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

int	get_args(char ***args, t_token *list)
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

int	get_here_doc_input(char *eof)
{
	char	*input;
	int		file;

	file = open(".here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	if (file < 0)
		perror(".here_doc.tmp open failure");
	while (1)
	{
		write (1, ">", 1);
		input = get_next_line(STDIN_FILENO);
		if (!input)
			printf("Invalid input\n");
		if (ft_strncmp(input, eof, ft_strlen(eof)) == 0)
		{
			free(input);
			break ;
		}
		write(file, input, ft_strlen(input));
		free(input);
	}
	close(file);
	file = open_here_doc();
	return (file);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab && *tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	if (tab)
		free(tab);
}

void	result_handler(int argc)
{
	int	i;

	i = 0;
	while (i < argc - 3)
	{
		wait(NULL);
		i++;
	}
	unlink(".here_doc.tmp");
}
