/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:21:20 by cwick             #+#    #+#             */
/*   Updated: 2024/10/17 15:00:16 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	if (!src)
		return (0);
	src_len = ft_strlen((char *)src);
	if (!dest)
		return (src_len);
	dest_len = ft_strlen(dest);
	i = 0;
	if (destsize <= dest_len)
	{
		return (src_len + destsize);
	}
	while ((i < src_len) && ((dest_len + i + 1) < destsize))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
