
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	cc;

	i = 0;
	cc = (char) c;
	while (str[i] != '\0')
	{
		if (str[i] == cc)
		{
			return ((char *) &str[i]);
		}
		i++;
	}
	if (str[i] == cc)
		return ((char *) &str[i]);
	return (NULL);
}
