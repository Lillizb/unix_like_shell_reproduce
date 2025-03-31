
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	src_length;

	i = 0;
	src_length = ft_strlen(src);
	if (src_length == 0)
	{
		if (destsize > 0)
			dest[0] = '\0';
		return (0);
	}
	if (destsize < 1)
		return (src_length);
	while (i < destsize && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_length);
}
