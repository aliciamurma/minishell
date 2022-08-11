/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurcia- <amurcia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:04:00 by aramirez          #+#    #+#             */
/*   Updated: 2022/08/11 18:47:53 by amurcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	pwd(void);
void	env(void);
void	export(char *name, char *content);
void	unset(char *name);
void    ft_others(char *path, char**argv);
// void	ft_look_for_flag(char *word);
// void	ft_print_the_echo(char **words);

//EXIT
void	ft_exit(char *str);
int		ft_its_not_digit(char *str, int len);
int		ft_after_exit(char *str, int count);
int		ft_empty_piece(char *str, int count);

//CD
void	ft_cd(char *input);
void	ft_parse_cd(char *input);
char	*ft_old_cd(void);
char	*ft_add_home_paths(char *word);

#endif