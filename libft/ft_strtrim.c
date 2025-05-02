#include "libft.h"
/**
* @brief Entfernt bestimmte Zeichen am Anfang und Ende eines Strings
*
* Diese Funktion erstellt einen neuen String, bei dem alle Zeichen aus 'set'
* am Anfang und Ende des Strings 's1' entfernt wurden. Der neue String wird
* dynamisch alloziert. Falls 's1' oder 'set' NULL sind, wird NULL
* zurückgegeben. Bei einem Speicherfehler während der Allokation wird
* ebenfalls NULL zurückgegeben. Der zurückgegebene String muss vom Aufrufer
* mit free() freigegeben werden, wenn er
* nicht mehr benötigt wird.
*
* @param s1 Der zu trimmende String
* @param set Ein String mit Zeichen, die vom Anfang und Ende entfernt
* 			werden sollen
* @return Ein neu allozierter getrimmter String oder NULL bei Fehlern
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*trimmed;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (start < end && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	trimmed = malloc((end - start) + 1);
	if (trimmed == NULL)
		return (NULL);
	i = 0;
	while (start < end)
	{
		trimmed[i] = s1[start];
		start++;
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
