#include "include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_token	*token;
	t_env	*env;
	t_gc	*gc;
	t_cmd	*cmds;

	gc = NULL;
	(void)ac;
	(void)av;
	gc_init(gc);
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
		// token = tokenize(input, gc);
		// if (!token)
		// {
		// 	gc_free(gc);
		// 	free_env(env);
		// 	free(input);
		// 	exit(2);
		// }
		// cmds = parse_tokens(token, env, gc);
		// if (token)
		// {
		// 	gc_free(gc);
		// 	free_env(env);
		// 	free(input);
		// 	exit(2);
		// }
		free(input);
	}
	gc_free(gc);
	free_env(env);
	return (0);
}
