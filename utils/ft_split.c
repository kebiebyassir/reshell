/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykebieb <ykebieb@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:28:56 by ykebieb           #+#    #+#             */
/*   Updated: 2025/06/15 22:29:58 by ykebieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_word(char const *s, char c)
{
	int	word;

	word = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			word++;
			while (*s != c && *s)
				s++;
		}
	}
	return (word);
}

static char	*put_word(char const *s, char c)
{
	int		len;
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

static void	ft_free(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

static int	words_split(char **str, const char *s, char c)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			str[i] = put_word(s, c);
			if (!str[i])
			{
				ft_free(str, i - 1);
				return (0);
			}
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	str = malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	if (!words_split(str, s, c))
		return (NULL);
	return (str);
}
