/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramirez <aramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:39:43 by amurcia-          #+#    #+#             */
/*   Updated: 2022/08/23 19:36:54 by aramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Comprueba si hay redirecciones
 * 
 * @param raw 
 * @return true 
 * @return false 
 */
bool    have_redirect(char *raw)
{
	int     i;
	bool    open_quote;
	char    quote;

	open_quote = false;
	i = 0;
	while (raw[i])
	{
		if (is_quote(raw[i]) && !open_quote)
		{
			open_quote = true;
			quote  = raw[i];
		}
		else if (is_quote(raw[i]) && raw[i] == quote)
			open_quote = !open_quote;
		if (is_redirect(raw[i]) && !open_quote)
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Comprueba el tipo de redireccion
 * 
 * @param raw is all the input between pipes
 * @param number of redirections
 * @return the redirection type
 */
t_redir_type get_redirect_type(char *raw, int number)
{
	int		count;
	int		redir;
	bool	open_quote;
	char	quote;

	(void) number;
	count = 0;
	redir = 0;
	open_quote = false;
	while (raw[count])
	{
		if (is_quote(raw[count]) && !open_quote)
		{
			open_quote = true;
			quote = raw[count];
		}
		if (is_quote(raw[count]) && raw[count] == quote)
			open_quote = !open_quote;
		if (raw[count] == '>' && raw[count + 1] == '>' && !open_quote)
			return (DOUBBLE_REIN);
		if (raw[count] == '<' && raw[count + 1] == '<' && !open_quote)
			return (DOUBBLE_REOUT);
		if (raw[count] == '<' && !open_quote)
			return (REOUT);
		if (raw[count] == '>' && !open_quote)
			return (REIN);
		count++;
	}
	return (REIN);
}

/**
 * @brief Comprueba el numero de redicciones
 * 
 * @param raw is all the input between pipes
 * @return quantity (int)
 */
int	get_redirect_quantity(char *raw)
{
	int		count;
	int		quantity;
	bool	open_quote;
	char	quote;

	count = 0;
	quantity = 0;
	open_quote = false;
	while (raw[count])
	{
		if (is_quote(raw[count]) && !open_quote)
		{
			open_quote = true;
			quote = raw[count];
		}
		else if (is_quote(raw[count]) && raw[count] == quote)
			open_quote = !open_quote;
		else if (is_redirect(raw[count]) && !open_quote)
		{
			if (raw[count] == raw[count + 1])
				count++;
			quantity++;
		}
		count++;
	}
	return (quantity);
}

// FILES hace referencia a FILES de la estructura s_redir_info
// AQUI NO ESTOY TENIENDO EN CUENTA SI ESTA ENTRE COMILLAS, ERA DEMASIADO
/**
 * @brief Extrae el contenido del input (el texto)
 * 
 * @param raw is all the input between pipes
 * @return text (char *)
 */
char	*extract_content_input(char *raw)
{
	int		count;
	int		i;
	char	*text;

	count = 0;
	i = 0;
	text = malloc(sizeof(char) * ft_strlen(raw) + 1);
	while (raw[count] == ' ' || raw[count] == '\t' || raw[count] == '\n')
		count++;
	while (raw[count] && (raw[count] != ' ' && raw[count] != '\t' && raw[count] != '\n'))
		count++;
	while (raw[count] == ' ' || raw[count] == '\t' || raw[count] == '\n')
		count++;
	if (raw[count] == '>' || raw[count] == '<')
		return (NULL);
	while (raw[count] && (raw[count] != ' ' && raw[count] != '\t' && raw[count] != '\n'))
	{
		text[i] = raw[count];
		i++;
		count++;
	}
	return (text);
}

/**
 * @brief Extrae el nombre del archivo (files)
 * 
 * @param raw is all the input between pipes
 * @param number
 * @return files (char *)
 */
char    *get_filename_redirect(char *raw, int number)
{
	(void) number;
	int		count;
	int		i;
	bool	open_quote;
	char	quote;
	char	*files;

	count = 0;
	i = 0;
	open_quote = false;
	files = malloc(sizeof(char) * ft_strlen(raw) + 1);
	while (raw[count])
	{
		if (is_quote(raw[count]) && !open_quote)
		{
			open_quote = true;
			quote = raw[count];
		}
		else if (is_quote(raw[count]) && raw[count] == quote)
			open_quote = !open_quote;
		else if ((raw[count] == '>' || raw[count] == '<') && !open_quote)
			break ;
		count++;
	}
	while (raw[count] == '>' || raw[count] == '<'
		|| raw[count] == ' ' || raw[count] == '\t' || raw[count] == '\n')
		count++;
	while (raw[count] && (raw[count] != ' ' && raw[count] != '\t' && raw[count] != '\n'))
	{
		files[i] = raw[count];
		i++;
		count++;
	}
	files[i] = '\0';
	return (files);
}

char	*get_input_redirect(char *raw)
{
	int		count;
	bool	open_quote;
	char	quote;

	count = 0;
	open_quote = false;
	quote = '\0';
	while (raw[count])
	{
		if (is_quote(raw[count]) && !open_quote)
		{
			exit(0);
			quote = raw[count];
		}
		else if (is_quote(raw[count]) && raw[count] == quote)
			open_quote = !open_quote;
		if ((raw[count] == '>' || raw[count] == '<') && !open_quote)
			break ;
		count++;
	}
	return (ft_substr(raw, 0, count));
}

void	get_input_parsed(char *raw, int process)
{
	int	count;

	g_minishell->process.content[process].redirs.quantity = 0;
	g_minishell->process.content->input = get_input_redirect(raw);
	if (have_redirect(raw))
	{
		g_minishell->process.content[process].redirs.quantity = get_redirect_quantity(raw);
		g_minishell->process.content[process].redirs.info = get_memory(sizeof(t_redir_info)
			* g_minishell->process.content[process].redirs.quantity, true);
		count = 0;
		while (count < g_minishell->process.content[process].redirs.quantity)
		{
			g_minishell->process.content[process].redirs.info[count].types = get_redirect_type(raw, count + 1);
			g_minishell->process.content[process].redirs.info[count].files = get_filename_redirect(raw, count + 1);
			printf("filename: %s\ntype: %i\n",g_minishell->process.content[process].redirs.info[count].files,g_minishell->process.content[process].redirs.info[count].types);
			count++;
		}
	}
}