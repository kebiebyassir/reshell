#include "include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_env	*env;
	t_gc	gc;

	(void)ac;
	(void)av;
	gc_init(&gc);
	env = dup_env(envp);
	while (1)
	{
		input = readline("ysh:~$ ");
		if(!input)
		{
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
	}
	free_env(env);
	return (0);
}
