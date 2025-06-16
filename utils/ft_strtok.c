/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykebieb <ykebieb@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:29:31 by ykebieb           #+#    #+#             */
/*   Updated: 2025/06/15 22:29:58 by ykebieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

char	*ft_strtok(char *str, const char *delim, int *index)
{
	char	*token;
	int		i;
	int		start;
	int		end;

	if (!str || !delim || !index)
		return (NULL);
	while (str[*index] && ft_strchr(delim, str[*index]))
		(*index)++;
	if (str[*index] == '\0')
		return (NULL);
	start = *index;
	while (str[*index] && !ft_strchr(delim, str[*index]))
		(*index)++;
	end = *index;
	token = malloc(end - start + 1);
	if (!token)
		return (NULL);
	i = 0;
	while (i < end - start)
	{
		token[i] = str[start + i];
		i++;
	}
	token[i] = '\0';
	return (token);
}
