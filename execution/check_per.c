#include "../include/minishell.h"

int check_per(t_cmd *cmd, t_env *env_list, t_gc *gc)
{
	struct stat st;
	char *path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strchr(cmd->args[0], '/'))
		path = ft_strdup_gc(cmd->args[0], gc);
	else
		path = get_path(cmd->args[0], env_list, gc);
	if (!path)
		return (1);
	if (stat(path, &st) != 0)
	{
		return (1);
	}
	if (S_ISDIR(st.st_mode))
	{
		return (1);
	}
	if (access(path, X_OK) != 0)
	{
		if (errno == EACCES)
		{
			return (126);
		}
		return (1);
	}
	return (0);
}
