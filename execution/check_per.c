#include "../include/minishell.h"

int check_per(t_cmd *cmd, t_env *env_list)
{
	struct stat st;
	char *path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strchr(cmd->args[0], '/'))
		path = ft_strdup(cmd->args[0]);
	else
		path = get_path(cmd->args[0], env_list);
	if (!path)
		return (1);
	if (stat(path, &st) != 0)
	{
		free(path);
		return (1);
	}
	if (S_ISDIR(st.st_mode))
	{
		free(path);
		return (1);
	}
	if (access(path, X_OK) != 0)
	{
		if (errno == EACCES)
		{
			free(path);
			return (126);
		}
		free(path);
		return (1);
	}
	free(path);
	return (0);
}
