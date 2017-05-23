#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
TODO: Implement a function that concatenates 2 strings (dest and source).
The return value should be the concatenated strings.
*/


char *string_concatenator(char *dest, char *source)
{
    printf("%d\n", strlen(dest));
    printf("%d\n", strlen(source));

    for (int i = strlen(dest); i < (strlen(source) + strlen(source)); i++) {
        dest[i] = source[i - strlen(dest)];
        printf("%s\n", dest);
        printf("%s\n", source);
        printf("%d\n", i);
    }
    dest[strlen(dest) + strlen(source)] = 'S';
    return *dest;
}


int main()
{
    char buff[256] = "kutya";
    char *example = "macska";
    *buff = string_concatenator(buff, example);
    puts(buff);
    return 0;
}
