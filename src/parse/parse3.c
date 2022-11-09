/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurcia- <amurcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:19:15 by amurcia-          #+#    #+#             */
/*   Updated: 2022/11/09 21:21:21 by amurcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input_parsed(t_pipe *command)
{
	int		count;
	char	*aux;

	command->redirs.quantity = 0;
	aux = get_input_redirect(command->raw);
	command->input = ft_trim(aux);
	free(aux);
	if (have_redirect(command->raw))
	{
		command->redirs.quantity = get_redirect_quantity(command->raw);
		command->redirs.info = ft_malloc(sizeof(t_redir_info)
				* command->redirs.quantity, false);
		count = 0;
		while (count < command->redirs.quantity)
		{
			command->redirs.info[count].types
				= get_redirect_type(command->raw, count + 1);
			command->redirs.info[count].files
				= get_filename_redirect(command->raw, count + 1);
			count++;
		}
	}
}

/**
 * @brief Contamos la cantidad de comillas, 
 * siempre y cuando no esten despues del \
 * 
 * @param raw 
 * @return true 
 * @return false 
 */
bool	is_odd_quotes(char *raw)
{
	int		count;
	int		q_simple;
	int		q_doubble;
	bool	open_quote;
	char	quote;

	count = 0;
	open_quote = false;
	q_simple = 0;
	q_doubble = 0;
	while (raw[count])
	{
		if (is_quote(raw[count]) && !open_quote)
		{
			open_quote = true;
			quote = raw[count];
			if (raw[count] == '"' && quote == '"')
				q_doubble++;
			else if (raw[count] == '\'' && quote == '\'')
				q_simple++;
		}
		else if (is_quote(raw[count]) && raw[count] == quote)
		{
			if (raw[count] == '"' && quote == '"')
				q_doubble++;
			else if (raw[count] == '\'' && quote == '\'')
				q_simple++;
			open_quote = !open_quote;
		}
		count++;
	}
	if (q_doubble % 2 == 0 && q_simple % 2 == 0)
        return (false);
	printf("Quotes not closed\n");
	return (true);
}
