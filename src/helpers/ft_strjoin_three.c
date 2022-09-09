/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramirez <aramirez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 20:39:27 by amurcia-          #+#    #+#             */
/*   Updated: 2022/09/09 13:39:46 by aramirez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	char	*s4;
	int		cont;
	int		conts4;

	cont = 0;
	conts4 = 0;
	s4 = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1)) + ft_strlen((char *)s3);
	if (!s4)
		return (0);
	while (s1[cont] != '\0')
	{
		s4[conts4] = s1[cont];
		cont++;
		conts4++;
	}
	cont = 0;
	while (s2[cont] != '\0')
	{
		s4[conts4] = s2[cont];
		cont++;
		conts4++;
	}
	cont = 0;
	while (s3[cont] != '\0')
	{
		s4[conts4] = s3[cont];
		cont++;
		conts4++;
	}
	s4[conts4] = '\0';
	return (s4);
}
