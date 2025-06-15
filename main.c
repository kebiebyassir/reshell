#include "include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_env	*env;

	(void)ac;
	(void)av;
	env = dup_env(envp);
	while (1)
	{
		input = readline("ysh:~$ ");
		if(!input)
		{
			printf("exit\n");
			break;
		}
		if (*input) // what this condition means
			add_history(input);

	}
	return (0);
}
