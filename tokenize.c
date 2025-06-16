#include "include/minishell.h"

t_lexer	*init_lexer(char	*input, t_gc *gc)
{
    t_lexer *lexer;

	lexer = gc_malloc(sizeof(t_lexer), gc);
	if (!lexer)
		return (NULL);
	lexer->input = input;
	lexer->pos = 0;
	lexer->len = ft_strlen(input);
	return (lexer);
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ' ' || c == '\t');
}

char	*read_word(t_lexer *lexer, t_gc *gc)
{
	int		start;
	char	quote;
	int		i;
	char	c;
	int		len;
	char	*word;

	start = lexer->pos;
	quote = 0;
	i = 0;
	// calculate the len excluding the quotes
	while (lexer->pos < lexer->len)
	{
		c = lexer->input[lexer->pos];
		// Handle quotes
		if ((c == '\'' || c == '"') && !quote)
		{
			quote = c;
			lexer->pos++;
			continue ;
		}
		if (c == quote)
		{
			quote = 0;
			lexer->pos++;
			continue ;
		}
		// If not in quotes and hit special char, stop
		if (!quote && is_special_char(c))
			break ;
		lexer->pos++;
	}
	// Extract the word
	len = lexer->pos - start;
	word = gc_malloc((len + 1), gc);
	if (!word)
		return (NULL);
	ft_strncpy(word, lexer->input + start, len);
	word[len] = '\0';
	return (word);
}

t_token	*create_token(t_token_type type, char *value, t_gc *gc)
{
	t_token	*token;

	token = gc_malloc(sizeof(t_token), gc);
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
		token->value = ft_strdup_gc(value, gc);
	else
		token->value = NULL;
	token->next = NULL;
	return (token);
}

void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->pos < lexer->len && (lexer->input[lexer->pos] == ' '
			|| lexer->input[lexer->pos] == '\t'))
		lexer->pos++;
}

t_token	*get_next_token(t_lexer	*lexer, t_gc *gc)
{
	char	c;
	char	*word;

	skip_whitespace(lexer);
	if (lexer->pos >= lexer->len)
		return (create_token(TOKEN_EOF, NULL, gc));
	c = lexer->input[lexer->pos];
	// Handle pipes
	if (c == '|')
	{
		lexer->pos++;
		return (create_token(TOKEN_PIPE, "|", gc));
	}
	// Handle redirections
	if (c == '<')
	{
		if (lexer->pos + 1 < lexer->len && lexer->input[lexer->pos + 1] == '<')
		{
			lexer->pos += 2;
			return (create_token(TOKEN_HEREDOC, "<<", gc));
		}
		lexer->pos++;
		return (create_token(TOKEN_REDIRECT_IN, "<", gc));
	}
	if (c == '>')
	{
		if (lexer->pos + 1 < lexer->len && lexer->input[lexer->pos + 1] == '>')
		{
			lexer->pos += 2;
			return (create_token(TOKEN_REDIRECT_APPEND, ">>", gc));
		}
		lexer->pos++;
		return (create_token(TOKEN_REDIRECT_OUT, ">", gc));
	}
	// Handle words (including quoted strings)
	word = read_word(lexer, gc);
	if (!word)
		return (NULL);
	return (create_token(TOKEN_WORD, word, gc));
}

t_token	*tokenize(char	*input, t_gc *gc)
{
	t_lexer	*lexer;
	t_token	*tokens;
	t_token	*current;
	t_token	*token;

	lexer = init_lexer(input, gc);
	if (!lexer)
		return (NULL);
	tokens = NULL;
	current = NULL;
	while ((token = get_next_token(lexer, gc)) && token->type != TOKEN_EOF)
	{
		if (!tokens)
		{
			tokens = token;
			current = token;
		}
		else
		{
			current->next = token;
			current = token;
		}
	}
	return (tokens);
}
