#include "../include/minishell.h"

int	is_builtin(t_cmd *cmds)
{
	if (!cmds || !cmds->args || !cmds->args[0])
		return (0);
	if (ft_strcmp(cmds->args[0], "exit") == 0)
		return (1);
	if (ft_strcmp(cmds->args[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmds->args[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmds->args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmds->args[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmds->args[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmds->args[0], "echo") == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_cmd *cmds, t_env *env_list, t_gc *gc)
{
	if (ft_strcmp(cmds->args[0], "exit") == 0)
		ft_exit(cmds->args);
	else if (ft_strcmp(cmds->args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmds->args[0], "env") == 0)
		ft_env(cmds->args, env_list);
	// else if (ft_strcmp(cmds->args[0], "cd") == 0)
	// 	ft_cd();
	// else if (ft_strcmp(cmds->args[0], "export") == 0)
	// 	ft_export();
	// else if (ft_strcmp(cmds->args[0], "unset") == 0)
	// 	ft_unset();
	// else if (ft_strcmp(cmds->args[0], "echo") == 0)
	// 	ft_echo();
}
