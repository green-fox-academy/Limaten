#include <stdio.h>
#include <stdlib.h>

int main()
{
    char name[50];
    int age;

    printf("Enter your first name please:\n");
    scanf("%s", &name);
    printf("Enter your age please:\n");
    scanf("%d", &age);
    printf("After %d years, %s will be 100 years old.\n", 100-age, name);
    return 0;
}
