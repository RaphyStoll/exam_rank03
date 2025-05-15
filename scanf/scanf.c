#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

int my_scanf(const char *format, ...) {
    char buffer[BUFFER_SIZE];
    char *bufptr;
    va_list args;
    int count = 0;

    // Lecture d'une ligne depuis l'entrée standard
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
        return -1;
    bufptr = buffer;

    va_start(args, format);
    for (const char *p = format; *p != '\0'; p++) {
        if (*p == '%') {
            p++; // Passage au caractère de format
            if (*p == 'd') {
                int *num = va_arg(args, int*);
                int value = 0;
                int sign = 1;

                // Ignorer les espaces initiaux
                while (*bufptr && isspace((unsigned char)*bufptr))
                    bufptr++;
                
                // Gérer le signe éventuel
                if (*bufptr == '-') {
                    sign = -1;
                    bufptr++;
                } else if (*bufptr == '+') {
                    bufptr++;
                }
                
                // Vérifier la présence d'au moins un chiffre
                if (!isdigit((unsigned char)*bufptr)) {
                    va_end(args);
                    return count;
                }
                
                // Conversion numérique : accumulation des chiffres
                while (*bufptr && isdigit((unsigned char)*bufptr)) {
                    value = value * 10 + (*bufptr - '0');
                    bufptr++;
                }
                *num = value * sign;
                count++;
            } else if (*p == 's') {
                // Conversion d'une chaîne de caractères
                char *str = va_arg(args, char*);
                int i = 0;
                // Ignorer les espaces initiaux
                while (*bufptr && isspace((unsigned char)*bufptr))
                    bufptr++;
                // Copier les caractères jusqu'à la fin du mot (séparé par un espace)
                while (*bufptr && !isspace((unsigned char)*bufptr)) {
                    str[i++] = *bufptr;
                    bufptr++;
                }
                str[i] = '\0';
                count++;
            }
            // D'autres formats peuvent être ajoutés ici...
        } else {
            // Si le caractère du format n'est pas '%', on le compare avec le caractère lu
            if (*bufptr == *p)
                bufptr++;
        }
    }
    va_end(args);
    return count;
}

int main(void) {
    int entier;
    char mot[100];

    printf("Entrez un entier puis un mot : ");
    // Utilisation de notre my_scanf
    if (my_scanf("%d %s", &entier, mot) != 2) {
        printf("Erreur de saisie.\n");
        return 1;
    }

    printf("Entier lu : %d\n", entier);
    printf("Mot lu    : %s\n", mot);
    return 0;
}