
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*str_join;

	i = 0;
	j = 0;
	str_join = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str_join)
		return (NULL);
	while (s1[i] != '\0')
	{
		str_join[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str_join[i] = s2[j];
		i++;
		j++;
	}
	str_join[i] = '\0';
	return (str_join);
}
