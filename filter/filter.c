#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1

void	ft_strlcat(char *dst, char *src) {
	int	i = 0;
	int	n = strlen(dst);

	while(src[i]) {
		dst[n] = src[i];
		i++;
		n++;
	}
	dst[n] = '\0';
}

char *read_str(void) {
	char tmp[BUFFER_SIZE + 1];
	char *buf;
	char *new_buf;
	int bytes_read = 1;
	int total_len = 0;

	buf = calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (perror("Error"), NULL);
	while ((bytes_read = read(0, tmp, BUFFER_SIZE)) > 0) {
		tmp[bytes_read] = '\0';
		total_len += bytes_read;
		new_buf = realloc(buf, total_len + 1);
		if (!new_buf) {
			free(buf);
			return (perror("Error"), NULL);
		}
		buf = new_buf;
		ft_strlcat(buf, tmp);
	}
	return(new_buf);
}

char *search_and_replace(char *str, char *needle) {
    int i = 0;
    int r = 0;
    int needle_len = strlen(needle);
    char *result;

    if (!str || !needle || needle_len == 0)
        return str;
    result = malloc(sizeof(char) * (strlen(str) + 1));
    if (!result) {
        printf("Error: malloc failed\n");
        return NULL;
    }
    while (str[i]) {
        int j = 0;
        while (j < needle_len && str[i + j] == needle[j])
            j++;
        if (j == needle_len) {
            for (j = 0; j < needle_len; j++)
                result[r++] = '*';          i += needle_len;
        } else {
            result[r++] = str[i++];
        }
    }
    result[r] = '\0';
    free(str);
    
    return result;
}


int main(int ac, char **av)
{
	char *input;
	char *result;

	if (ac < 2)
		return (1);
	input = read_str();
	if (!input)
		return (1);
	result = search_and_replace(input, av[1]);
	if (!result)
		return (1);
	printf("%s\n", result);
	free(result);
	return (0);
}