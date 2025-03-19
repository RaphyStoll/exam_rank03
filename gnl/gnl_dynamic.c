#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

// Fonctions utilitaires
static int ft_strlen(char *str)
{
    int i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

static char *ft_strchr(char *str, char c)
{
    int i = 0;
    if (!str)
        return (NULL);
    while (str[i])
    {
        if (str[i] == c)
            return (&str[i]);
        i++;
    }
    return (NULL);
}

static char *ft_strjoin(char *s1, char *s2)
{
    int i = 0;
    int j = 0;
    char *result;

    if (!s1)
    {
        s1 = malloc(1);
        if (!s1)
            return (NULL);
        s1[0] = '\0';
    }
    if (!s2)
        return (s1);
    result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!result)
        return (NULL);
    while (s1[i])
    {
        result[i] = s1[i];
        i++;
    }
    while (s2[j])
        result[i++] = s2[j++];
    result[i] = '\0';
    free(s1);
    return (result);
}

// Extrait la ligne du buffer
static char *extract_line(char *buffer)
{
    int i = 0;
    char *line;

    if (!buffer || !buffer[0])
        return (NULL);
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (buffer[i] == '\n')
        i++;
    line = malloc(i + 1);
    if (!line)
        return (NULL);
    i = 0;
    while (buffer[i] && buffer[i] != '\n')
    {
        line[i] = buffer[i];
        i++;
    }
    if (buffer[i] == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return (line);
}

// Met à jour le buffer après extraction d'une ligne
static char *update_buffer(char *buffer)
{
    int i = 0;
    int j = 0;
    char *new_buffer;

    if (!buffer)
        return (NULL);
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (!buffer[i])
    {
        free(buffer);
        return (NULL);
    }
    i++;
    new_buffer = malloc(ft_strlen(buffer) - i + 1);
    if (!new_buffer)
        return (NULL);
    while (buffer[i])
        new_buffer[j++] = buffer[i++];
    new_buffer[j] = '\0';
    free(buffer);
    return (new_buffer);
}

// Fonction principale
char *get_next_line(int fd)
{
    static char *buffer;
    char *line;
    char *temp;
    int bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    temp = malloc(BUFFER_SIZE + 1);
    if (!temp)
        return (NULL);
    bytes_read = 1;
    while (!ft_strchr(buffer, '\n') && bytes_read > 0)
    {
        bytes_read = read(fd, temp, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(temp);
            return (NULL);
        }
        temp[bytes_read] = '\0';
        buffer = ft_strjoin(buffer, temp);
    }
    free(temp);
    line = extract_line(buffer);
    buffer = update_buffer(buffer);
    return (line);
}