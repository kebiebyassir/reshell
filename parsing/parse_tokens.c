#include "include/minishell.h"

t_cmd	*init_cmd(t_gc *gc)
{
	t_cmd	*cmd;

	cmd = gc_malloc(sizeof(t_cmd), gc);
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append_mode = 0;
	cmd->heredoc_delimiter = NULL;
	cmd->next = NULL;
	cmd->has_redirection = 0;
	cmd->is_ambiguous = 0;
	return (cmd);
}

char	*get_env_value(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*expand_variable(char *str, t_env *env, t_gc *gc)
{
	char	*var_name;
	char	*var_value;
	int		i;

	if (!str || !ft_strchr(str, '$'))
		return (ft_strdup_gc(str, gc));
	if (str[0] == '$')
	{
		i = 1;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		var_name = gc_malloc(i, gc);
		ft_strncpy(var_name, str + 1, i - 1);
		var_name[i - 1] = '\0';
		var_value = get_env_value(env, var_name);
		if (!var_value)
			return (ft_strdup_gc("", gc)); // Return empty if var not found
		return (ft_strdup_gc(var_value, gc));
	}
	return (ft_strdup_gc(str, gc));
}

int	add_arg_to_cmd(t_cmd *cmd, char *arg, t_env *env, t_gc *gc)
{
	char	*expanded_arg;
	int		count;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	cmd->args = ft_realloc(cmd->args, sizeof(char *) * (count + 2), gc);
	if (!cmd->args)
		return (0);
	expanded_arg = expand_variable(arg, env, gc);
	cmd->args[count] = ft_strdup_gc(arg, gc);
	cmd->args[count + 1] = NULL;
	return (1);
}

int	handle_redirection(t_cmd *cmd, t_token **myToken)
{
	t_token	*token;
	char	*filename;

	token = *myToken;
	cmd->has_redirection = 1;
	if (!token->next || token->next->type != TOKEN_WORD)
	{
		ft_printf("minishell: syntax error near unexpected token `%s`\n", token->next->value);
		return (0);
	}
	filename = token->next->value;
	if (token->type == TOKEN_REDIRECT_IN) // <
	{
		if (cmd->input_file)
			free(cmd->input_file);
		cmd->input_file = ft_strdup(filename);
	}
	else if (token->type == TOKEN_REDIRECT_OUT) // >
	{
		if (cmd->output_file)
			free(cmd->output_file);
		cmd->output_file = ft_strdup(filename);
		cmd->append_mode = 0;
	}
	else if (token->type == TOKEN_REDIRECT_APPEND) // >>
	{
		if (cmd->output_file)
			free(cmd->output_file);
		cmd->output_file = ft_strdup(filename);
		cmd->append_mode = 1;
	}
	else if (token->type == TOKEN_HEREDOC) // <<
	{
		if (cmd->heredoc_delimiter)
			free(cmd->heredoc_delimiter);
		cmd->heredoc_delimiter = ft_strdup(filename);
	}
	else
	{
		printf("Error: Unknown redirection type\n");
		return (0);
	}
	*myToken = token->next;
	return (1);
}

t_cmd	*parse_command(t_token **tokens, t_env *env, t_gc *gc)
{
	t_cmd	*cmd;
	t_token	*current;

	cmd = init_cmd(gc);
	if (!cmd)
		return (NULL);
	current = *tokens;
	while (current && current->type != TOKEN_PIPE && current->type != TOKEN_EOF)
	{
		if (!current->value)
			current->value = "NULL";
		if (current->type == TOKEN_WORD)
		{
			if (!add_arg_to_cmd(cmd, current->value, env, gc))
				return (NULL);
		}
		else if (current->type == TOKEN_REDIRECT_IN
			|| current->type == TOKEN_REDIRECT_OUT
			|| current->type == TOKEN_REDIRECT_APPEND
			|| current->type == TOKEN_HEREDOC)
		{
			if (!handle_redirection(cmd, &current))
				return (NULL);
		}
		else
		{
			ft_printf("\nError: Unexpected token type %d\n", current->type);
			return (NULL);
		}
		current = current->next;
	}
	*tokens = current;
	return (cmd);
}

t_cmd	*parse_tokens(t_token *tokens, t_env *env, t_gc *gc)
{
	t_cmd	*first_cmd;
	t_token	*current_token;
	t_cmd	*new_cmd;
	t_cmd	*current_cmd;

	if (!tokens)
		return (NULL);
	first_cmd = NULL;
	current_cmd = NULL;
	current_token = tokens;
	while (current_token && current_token->type != TOKEN_EOF)
	{
		new_cmd = parse_command(&current_token, env, gc);
		if (!new_cmd)
		{
			return (NULL);
		}
		if (!first_cmd)
		{
			first_cmd = new_cmd;
			current_cmd = new_cmd;
		}
		else
		{
			current_cmd->next = new_cmd;
			current_cmd = new_cmd;
		}
		if (current_token && current_token->type == TOKEN_PIPE)
		{
			current_token = current_token->next; // Skip khfif lpipe
		}
	}
	return (first_cmd);

}

int	validate_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (!current || current->type == TOKEN_EOF)
	{
		printf("Error: Empty command\n");
		return (0);
	}
	// Check if starts with pipe
	if (current->type == TOKEN_PIPE)
	{
		printf("Error: Command cannot start with pipe\n");
		return (0);
	}
	while (current && current->type != TOKEN_EOF)
	{
		// Check pipe followed by pipe or EOF
		if (current->type == TOKEN_PIPE)
		{
			if (!current->next || current->next->type == TOKEN_EOF)
			{
				printf("Error: Pipe without command\n");
				return (0);
			}
			if (current->next->type == TOKEN_PIPE)
			{
				printf("Error: Invalid double pipe\n");
				return (0);
			}
		}
		// Check redirections followed by non-word
		if (current->type == TOKEN_REDIRECT_IN
			|| current->type == TOKEN_REDIRECT_OUT
			|| current->type == TOKEN_REDIRECT_APPEND
			|| current->type == TOKEN_HEREDOC)
		{
			if (!current->next || current->next->type != TOKEN_WORD)
			{
				printf("Error: Redirection without filename\n");
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}
