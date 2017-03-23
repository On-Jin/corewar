/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 20:08:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/02/26 18:46:25 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

void	*ft_memrealloc(void *ptr, size_t size_old, size_t size_new)
{
	void	*new_ptr;

	new_ptr = (void*)malloc(size_new);
	if (new_ptr == NULL)
		return (NULL);
	if (ptr)
		new_ptr = ft_memcpy(new_ptr, ptr, size_old);
	if (ptr)
		free(ptr);
	return (new_ptr);
}
