
#include "libft.h"

void	*ft_memchr(const void *s, size_t c, size_t n)
{
	size_t				i;
	const unsigned char	*sc;
	unsigned char		cc;

	i = 0;
	sc = (unsigned char *) s;
	cc = (unsigned char) c;
	while (i < n)
	{
		if (sc[i] == cc)
			return ((void *) sc + i);
		i++;
	}
	return (NULL);
}
