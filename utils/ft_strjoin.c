/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykebieb <ykebieb@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:29:19 by ykebieb           #+#    #+#             */
/*   Updated: 2025/06/15 22:29:58 by ykebieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc(s1_len + s2_len);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
		while (s1[j] != '\0')
			str[i++] = s1[j++];
	j = 0;
	if (s2)
		while (s2[j] != '\0')
			str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
