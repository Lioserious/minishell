#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	cc;

	cc = (unsigned char) c;
	i = ft_strlen(s);
	if (cc == '\0')
		return ((char *)(s + i));
	while (i > 0)
	{
		if (s[i - 1] == (unsigned char)c)
		{
			return ((char *)(s + i - 1));
		}
		i--;
	}
	return (NULL);
}
