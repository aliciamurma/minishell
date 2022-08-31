/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramirez <aramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 23:34:47 by aramirez          #+#    #+#             */
/*   Updated: 2022/08/12 15:24:34 by aramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Comprueba si el string es un path valido
 * 
 * @param str path
 * @return true 
 * @return false 
 */
bool	is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Crea un array en el que esta el title y el content de env
 * 
 * @param void 
 */
void	ft_env_array(void)
{
	char	**env;
	int		len;
	int		i;

	i = 0;
	env = get_memory(sizeof(char) * g_minishell->env.count + 1, true);
	env[g_minishell->env.count] = NULL;
	while (i < g_minishell->env.count)
	{
		len = (ft_strlen(g_minishell->env.vars[i].title)
				+ ft_strlen(g_minishell->env.vars[i].content));
		env[i] = get_memory(sizeof(char) * len + 1, true);
		env[i] = ft_strjoin_three(g_minishell->env.vars[i].title,
				"=", g_minishell->env.vars[i].content);
		i++;
	}
}

/**
 * @brief Ejecuta un programa
 * 
 * @param path 
 */
void	ft_others(char *path)
{
	char	**argv;

	argv = ft_split_quotes(ft_trim(path), ' ');
	path = argv[0];
	if (!is_path(path))
	{
		printf("%s: command not found\n", path);
		return ;
	}
	if (access(path, F_OK) == -1)
	{
		printf("%s: No such file or directory\n", path);
		return ;
	}
	if (access(path, X_OK) == -1)
	{
		printf("permission denied: %s\n", path);
		return ;
	}
	execve(path, argv, argv);
}
