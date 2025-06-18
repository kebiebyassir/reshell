#include "../../include/minishell.h"

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

void	execute_builtin(t_cmd *cmds, t_env *env_list)
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

char	*get_path(char *cmd, t_env *env_list)
{
	t_env	*cur;
	char	**path;
	char	*command;
	int		i;

	cur = env_list;
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
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
		command = ft_strjoin(path[i], "/");
		command = ft_strjoin(command, cmd);
		if (access(command, X_OK) == 0)
		{
			return (command);
		}
		free(command);
		i++;
	}
	return (NULL);
}

void	execute_command(t_cmd *cmds, char **envp, t_env *env_list)
{
	pid_t	pid;
	char	*path;
	int		checker;
	int		redirect_status;

	if (!cmds || !cmds->args || !cmds->args[0])
		return ;
	if (is_builtin(cmds))
	{
		execute_builtin(cmds, env_list);
		return ;
	}
	checker = check_per(cmds, env_list);
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
			redirect_status = redirection_out(cmds, env_list, envp);
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
		path = get_path(cmds->args[0], env_list);
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
