/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykebieb <ykebieb@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:27:06 by ykebieb           #+#    #+#             */
/*   Updated: 2025/06/16 18:35:19 by ykebieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_realloc(void *ptr, size_t size, t_gc *gc)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (gc_malloc(size, gc));
	if (!size)
		return (ptr);
	new_ptr = gc_malloc(size, gc);
	if(new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	return (new_ptr);
}
