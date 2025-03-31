
#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	int		i;
	int		s_len;
	char	*new_s;

	i = 0;
	s_len = ft_strlen(s);
	new_s = (char *) malloc((s_len + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	while (i < s_len)
	{
		new_s[i] = (*f)(i, s[i]);
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
