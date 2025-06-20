#include "../include/minishell.h"


int	redirection_out(t_cmd *cmd, t_env *env_list, char **envp)
{
	struct stat st;
	int	status;
	int fd;
	int flag;
	pid_t pid;
	char *path;

	flag = 0;

	if (!cmd->output_file)
	{
		ft_printf("minishell: syntax error near unexpected token `newline`\n");
		return (2);
	}
	if (stat(cmd->output_file, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_printf("minishell: %s: Is a directory\n", cmd->output_file);
		return (1);
	}
	if (cmd->is_ambiguous)
	{
		ft_printf("minishell: %s: ambiguous redirect\n", cmd->output_file);
		return (1);
	}
	status = check_per(cmd, env_list);
	if (status == 1)
	{
		fd = open(cmd->output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd >= 0)
			close(fd);
		ft_printf("%s: command not found\n", cmd->args[0]);
		return (127);
	}
	else if (status == 126)
	{
		fd = open(cmd->output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd >= 0)
			close(fd);
		ft_printf("minishell: %s: Permission denied\n", cmd->args[0]);
		return (126);
	}
	else if (status == 0)
	{
		flag = 1;
	}
	else
	{
		fd = open(cmd->output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd >= 0)
			close(fd);
		ft_printf("%s: command not found\n", cmd->args[0]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		if (flag)
		{
			fd = open(cmd->output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
			{
				ft_printf("minishell: %s: %s\n", cmd->output_file, strerror(errno));
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		path = get_path(cmd->args[0], env_list);
		if (!path)
		{
			ft_printf("%s: command not found\n", cmd->args[0]);
			exit(127);
		}
		execve(path, cmd->args, envp);
		ft_printf("%s: execution failed\n", cmd->args[0]);
		free(path);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		int wstatus;
		waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			return WEXITSTATUS(wstatus);
		return 1;
	}
	else
	{
		ft_printf("fork failed\n");
		return 1;
	}
}
