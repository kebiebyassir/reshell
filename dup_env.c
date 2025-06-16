#include "include/minishell.h"

t_env	*create_env(char *envp)
{
	t_env	*new;
	size_t	i;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	new->key = ft_substr(envp, 0, i);
	if (!new->key)
	{
		free(new);
		return(NULL);
	}
	if (envp[i] == '=' && envp[i + 1])
	{
		new->value = ft_strdup((envp + i + 1));
		if (!new->value)
		{
			free(new->key);
			free(new);
			return (NULL);
		}
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

t_env	*dup_env(char **envp)
{
	t_env	*env_list;
	t_env	*head;
	t_env	*last;

	head = NULL;
	last = NULL;
	while (*envp)
	{
		env_list = create_env(*envp);
		if (!env_list)
			return (NULL);
		if (!head)
			head = env_list;
		else
			last->next = env_list;
		last = env_list;
		envp++;
	}
	return (head);
}

void	free_env(t_env	*env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

// print for debug
void	print_env(t_env *env)
{
	while (env)
	{
		if (env->key)
		{
			printf("%s", env->key);
			if (env->value)
				printf("=%s", env->value);
			printf("\n");
		}
		env = env->next;
	}
}
