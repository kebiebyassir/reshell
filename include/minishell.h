#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_gc_list
{
	void				*ptr;
	struct s_gc_list	*next;
}	t_gc_list;

typedef struct s_gc
{
	t_gc_list	*head;
}	t_gc;


// duplicate environnement
t_env	*create_env(char *envp);
t_env	*dup_env(char **envp);
void	free_env(t_env	*env);
void	print_env(t_env *env);

#endif
