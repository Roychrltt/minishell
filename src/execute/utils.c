/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiaxu <xiaxu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:36:30 by xiaxu             #+#    #+#             */
/*   Updated: 2024/09/01 16:21:52 by xiaxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*my_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	if (len1)
		ft_strlcpy(res, s1, len1 + 1);
	if (len2)
		ft_strlcpy((res + len1), s2, len2 + 1);
	if (s1)
		free(s1);
	return (res);
}
/*
int	open_file(char *file, int n)
{
	int	fd;

	fd = -1;
	if (n == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			perror_message("Infile open failure");
	}
	else if (n == 1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if (fd == -1)
			perror_message("Outfile open failure");
	}
	else if (n == 2)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		if (fd == -1)
			perror_message("Outfile open failure");
	}
	return (fd);
}
*/

char	**get_paths(t_env *env)
{
	char	*s;
	char	**paths;

	s = ft_strdup(my_getenv("PATH", env));
	if (!s)
		return (NULL);
	paths = ft_split(s, ':');
	free(s);
	if (!paths)
		return (NULL);
	return (paths);
}

/*
char	*get_command(char **path, char *cmd)
{
	int		i;
	char	*try;
	char	*command;

	i = 0;
	while (paths[i])
	{
		try = ft_strjoin(paths[i], "/");
		command = ft_strjoin(try, cmd);
		free(try);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}
*/

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
