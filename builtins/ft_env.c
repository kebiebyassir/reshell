#include "../include/minishell.h"

int	ft_env(char **cmds, t_env *env_list)
{
	if (cmds[1])
	{
		ft_printf("minishell: env: '%s': No such file or directory\n", cmds[1]);
		return (127);
	}
	while (env_list)
	{
		if (env_list->value != NULL)
			printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
	return (0);
}
