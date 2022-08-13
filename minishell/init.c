/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurcia- <amurcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:30:13 by amurcia-          #+#    #+#             */
/*   Updated: 2022/08/13 19:37:02 by amurcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Obtenemos el mensaje que pasamos por la shell
*/
char	*ft_get_input(void)
{
	print_prompt();
	return (readline(" "));
}

/*
* Leemos en bucle
*/
void	ft_read(void)
{
	while (1)
	{
		g_minishell->input = ft_get_input();
		if (!g_minishell->input)
		{
			printf("exit\n");
			close_minishell();
		}
		else if (*g_minishell->input != '\0')
		{
			ft_read_history();
			ft_parse();
		}
		free(g_minishell->input);
	}
	ft_clear_history();
}

/*
* Cuando comenzamos el programa, status = 0
* Iniciamos las senales antes de leer
*/
void	ft_signal(void)
{
	g_minishell->status = 0;
	ft_get_signal();
}

/*
* Iniciamos g_minishell
* Iniciamos environment
*/
void	ft_init_minishell(char **env)
{
	g_minishell = get_memory(sizeof(t_minishell));
	init_env(env);
	update_env_var("PWD", "minishell");
	ft_signal();
	ft_read();
}