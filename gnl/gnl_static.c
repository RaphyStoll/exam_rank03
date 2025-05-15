#include "get_next_line.h"


//1.strdup.c
// 1.1 compter la len
// 1.2 malloc
// 1.3 copier
// 1.4 return
//2. get_next_line
// 2.1 verifier si fd et BUFFER_SIZE est valide
// 2.3 lire le buffer
// 3.4 copier le buffer dans line
// 3.5 verifier si = '\n' ou '\0' si oui break
// 3.6 ajouter '\0' a la fin de line

char *ft_strdup(char *src) {
	char *dest;
	int i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while(src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int buf_pos;
	static int buf_read;
	int i = 0;
	char line[70000];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	while (1) {
		if (buf_pos >= buf_read)
		{
			buf_read = read(fd, buffer, BUFFER_SIZE);
			if (buf_read <= 0)
				break;
			buf_pos = 0;
		}
		line[i++] = buffer[buf_pos++];
		if (buffer[buf_pos] == '\n')
			break;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}
