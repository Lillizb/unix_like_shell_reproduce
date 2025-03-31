
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	cc;
	char	*find;

	i = 0;
	cc = (char) c;
	find = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == cc)
		{
			find = ((char *) &str[i]);
		}
		i++;
	}
	if (str[i] == cc)
		find = ((char *) &str[i]);
	return (find);
}
