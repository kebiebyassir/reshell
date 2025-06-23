#include "../include/minishell.h"

char	*get_path(char *cmd, t_env *env_list, t_gc *gc)
{
	t_env	*cur;
	char	**path;
	char	*command;
	int		i;

	cur = env_list;
	if (ft_strchr(cmd, '/'))
		return (ft_strdup_gc(cmd, gc));
	while (cur && ft_strcmp(cur->key, "PATH") != 0)
		cur = cur->next;
	if (!cur || !cur->value)
		return (NULL);
	path = ft_split(cur->value, ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		command = ft_strjoin(path[i], "/", gc);
		command = ft_strjoin(command, cmd, gc);
		if (access(command, X_OK) == 0)
		{
			return (command);
		}
		i++;
	}
	return (NULL);
}

void	execute_command(t_cmd *cmds, char **envp, t_env *env_list, t_gc *gc)
{
	pid_t	pid;
	char	*path;
	int		checker;
	int		redirect_status;

	if (!cmds || !cmds->args || !cmds->args[0])
		return ;
	if (is_builtin(cmds))
	{
		execute_builtin(cmds, env_list, gc);
		return ;
	}
	checker = check_per(cmds, env_list, gc);
	if (checker == 1)
	{
		ft_printf("%s: command not found\n", cmds->args[0]);
		return;
	}
	else if (checker == 126)
	{
		ft_printf("minishell: %s: Permission denied\n", cmds->args[0]);
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if (cmds->output_file)
		{
			redirect_status = redirection_out(cmds, env_list, envp, gc);
			if (redirect_status != 0)
			{
				exit(redirect_status);
			}
		}
		if (cmds->has_redirection && !cmds->output_file)
		{
			ft_printf("minishell: syntax error near unexpected token 'newline'\n");
			return;
		}
		path = get_path(cmds->args[0], env_list, gc);
		if (!path)
		{
			ft_printf("%s: command not found\n", cmds->args[0]);
			exit(127);
		}
		execve(path, cmds->args, envp);
		perror(cmds->args[0]);
		free(path);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork");
}
