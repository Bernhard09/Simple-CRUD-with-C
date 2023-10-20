#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "cs50.h"

int main(int argc, char const *argv[])
{
    FILE *file = fopen("database.txt", "r");
    char *buffer = malloc(50 * sizeof(char));
    char *idk;

    
    printf("%s\n", fgets(buffer, 50, file));

    fclose(file);
    free(buffer);
    

}   
