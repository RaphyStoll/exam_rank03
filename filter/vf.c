#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	ft_strlcat(char *dst, char *src) {
	int i = 0;
	int len = strlen(dst);
	while (src[i]) {
		dst[len++] = src[i++];
	}
	dst[len] = '\0';
}

int	ft_strncmp(const char *s1, const char *s2, int n) {
	int i = 0;

	while (s1[i] && s2[i] && i < n) {
		if (s1[i] != s2[i])
			return 1;
		i++;
	}
	if (i < n)
		return 1;
	return 0;
}

char *read_str(void) {
	char	buffer[2];
	char	*result;
	int		readed = 0;
	int		total_len = 0;
	int		i = 0;

	result = calloc(1, 1);
	if (!result)
		return NULL;
	while ((readed = read(0, buffer, 1)) > 0) {
		buffer[readed] = '\0';
		total_len += readed;
		result = realloc(result, total_len + 1);
		if (!result)
			return NULL;
		result[i] = buffer[0];
		i++;
		result[i] = '\0';
	}
	return result;
}

char *search_and_replace(char *str, char *needle)
{
	int i = 0;
	int j = 0;
	int r = 0;
	int needle_len = strlen(needle);
	char *result;

	if (!str || !needle || needle_len == 0)
		return str;
	result = malloc(sizeof(char) * (strlen(str) + 1));
	if (!result)
		return NULL;
	while (str[i])
	{
		j = 0;
		if (!ft_strncmp(&str[i], needle, needle_len)) {
			while (j < needle_len)
			{
				result[r++] = '*';
				j++;
			}
			i += needle_len;
		}
		else
			result[r++] = str[i++];                         
	}
	result[r] = '\0';
	return result;
}


int main(int ac, char **av) {
	if (ac < 2)
		return 1;

	char *input = read_str();
	if (!input)
		return (1);
	
		char *result = search_and_replace(input, av[1]);
	if (!result)
		return (free(input), 1);

	printf("%s", result);
	
	free(input);
	free(result);
	return 0;
}