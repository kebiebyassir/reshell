/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_gc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykebieb <ykebieb@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:29:05 by ykebieb           #+#    #+#             */
/*   Updated: 2025/06/16 16:00:10 by ykebieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strdup_gc(const char *s, t_gc *gc)
{
	char	*dup;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	dup = gc_malloc(((len + 1) * sizeof(char)), gc);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
