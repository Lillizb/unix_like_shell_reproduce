
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	actual_len;

	actual_len = len;
	if (!s)
		return (NULL);
	if ((size_t) start >= ft_strlen(s))
		return (ft_strdup(""));
	if (actual_len > ft_strlen(s + start))
		actual_len = ft_strlen(s + start);
	substring = (char *)malloc((actual_len + 1) * sizeof(char));
	if (substring == NULL)
		return (NULL);
	ft_strlcpy(substring, s + start, actual_len + 1);
	return (substring);
}
