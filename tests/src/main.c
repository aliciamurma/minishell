#include "minishell.h"
#include "test.h"

t_minishell	*g_minishell;

int main(int argc, char *argv[], char *envp[])
{
	// t_minishell	*minishell;

    (void)argc;
    (void)argv;
    (void)envp;


    create_pipe(3);
	// minishell = malloc(sizeof(t_minishell));
	// if (!minishell)
	// 	return (-1);
    // ft_parse(minishell);
    return (0);
}
