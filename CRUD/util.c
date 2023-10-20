#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "cs50.h"

typedef struct 
{
    char *Name;
    char *Author;
    char *Publisher;
    int Year;
}
books;

void createInfo()
{   
    // clear system
    system("cls");


    // declaration
    books book;

    book.Name = malloc(sizeof(char) * 100);
    book.Author = malloc(sizeof(char) * 100);
    book.Publisher = malloc(sizeof(char) * 100);

    
    FILE *create = fopen("database.txt", "a");

    if(create == NULL)
    {
        perror("File not found");
        exit(404);
    }


    // getting information from user
    printf("Create :\n");
    printf("----------------------------\n");

    do
    {   
        fflush(stdin);
        book.Name = get_string("Nama Buku: ");
    }
    while(book.Name == NULL || book.Name[0] == '\n');

    do
    {
        fflush(stdin); 
        book.Author = get_string("Nama Penulis: ");
    }
    while(book.Author == NULL || book.Author[0] == '\n'); // if book.Author is NULL or book.Author only a newline -> keep prompting the user

    do
    {
        fflush(stdin); 
        book.Publisher = get_string("Nama Publisher: ");
    }
    while(book.Publisher == NULL || book.Publisher[0] == '\n'); // if book.Publisher is NULL or book.Publisher only a newline -> keep prompting the user


    fflush(stdin);

    printf("Tahun Terbit: ");
    scanf("%i", &book.Year);
    
    
    // put the given information to database
    fprintf(create,"%s_%s_%i_%s\n", book.Name, book.Author, book.Year, book.Publisher);
    
    printf("----------------------------\n");
    printf("Creating Info...\n");
    Sleep(2000);

    
    // free the memory
    fflush(stdin);
    fclose(create);
    free(book.Name);
    free(book.Author);
    free(book.Publisher);

}

void readInfo()
{   
    // declaration
    char ch[5][50];
    char *buffer = malloc(sizeof(char) * 255);
    char *token;
    char isContinue;
    int number = 0;

    system("cls");

    // membuka file database
    FILE *read = fopen("database.txt", "r");
    if (read == NULL)
    {
        perror("File not found.\n");
        exit(404);
    }


    
    // print to screen
    printf("NO \t Nama Buku \t Penulis \t Tahun Terbit \t Publisher\n");
    printf("-------------------------------------------------------------------\n");
    
    // membaca file sampai akhir baris
    while(fgets(buffer, 50, read))
    {   
        number++;

        // slice string with "_"
        token = strtok(buffer, "_");
        for (int i = 0; token != NULL && i < 5; i++)
        {   
            strcpy(ch[i], token);
            token = strtok(NULL, "_");
        }

        // print to screen
        printf("%i \t %s \t %s  %7s \t\t %s\n", number, ch[0], ch[1], ch[2], ch[3]);
    }

    
    fflush(stdin);
    free(buffer);
    fclose(read);
}


void updateInfo()
{   
    // declaration
    FILE *main_file, *temp_file;
    int line_no, count = 1;
    char *token;
    char words[5][50];
    char prompt[][50] = {"Nama Buku: ", "Nama Penulis: ", "Tahun Terbit: ", "Nama Publisher: "};
    char *wordTemp = malloc(sizeof(char) * 10);
    char *buffer = malloc(sizeof(char) * 100);

    // open file in r mode
    main_file = fopen("database.txt", "r");

    // read database
    readInfo();

    // ask user what data that want to be update
    printf("Input no data want to update: ");
    scanf("%i", &line_no);

    // get data info
    while (fgets(buffer, 100, main_file))
    {   
        if (count == line_no)
        {
            token = strtok(buffer, "_");
            for (int i = 0; token != NULL && i<5; i++)
            {   
                strcpy(words[i], token); 
                token = strtok(NULL, "_");
            }
            fclose(main_file);
            count = 1;
            break; 
                      
        }
        count++;
    }
    // update data to db
    // update info
    for (int i = 0; i < 4; i++)
    {   
        fflush(stdin);
        strcpy(wordTemp, words[i]); 
        string inputTemp = get_string(prompt[i]);
        char newLn = '\n';
        if (strcmp(inputTemp, "") == 0)
        {
            strcpy(words[i], wordTemp);
            
        } 
        else
        {   
            if (i == 3)
            {
                strncat(inputTemp, &newLn, 1);
            }
            strcpy(words[i], inputTemp);
           
        }
    }
        
    // open tempfile & reopen main file to clear file stream
    main_file = fopen("database.txt", "r");
    temp_file = fopen("___temp.txt", "w");
    while (fgets(buffer, 50, main_file))
    {   

        if (count == line_no)
        {
            printf("condition 1: count %i\n", count);
            printf("%s_%s_%i_%s", words[0], words[1], atoi(words[2]), words[3]);
            fprintf(temp_file, "%s_%s_%i_%s", words[0], words[1], atoi(words[2]), words[3]);
        }
        else
        {   
            
            printf("condition 2: count %i\n", count);
            printf("Buffer: %s", buffer);
            fprintf(temp_file, "%s", buffer);
        }
        

        count++;
    }
    fflush(stdin);

    // free memory and closed file
    free(buffer);
    fclose(main_file);
    fclose(temp_file);

    // updating file
    printf("Updating...\n");
    remove("database.txt");
    rename("___temp.txt", "database.txt");
    Sleep(1500);

}


void deleteInfo()
{
    // declaration
    FILE *main_file, *temp_file;
    char *buffer = malloc(sizeof(char) * 255);
    int line_no;
    int count = 1;    

    // open main file in r mode
    main_file = fopen("database.txt", "r");

    // read all data in main file
    readInfo();

    // user input the specific line that want to delete
    do{
    
    printf("Nomor data yang ingin dihapus: ");
    scanf("%i", &line_no);

    }
    while(false);

    // if user doesn't urge to delete file, pass all the code below all the way down

    // open temp file in w mode
    temp_file = fopen("___temp.txt", "w");
    if (temp_file == NULL)
    {
        printf("File not found.");
        exit(404);
    }

    // search the wanted deleted file
    // if system find the unwanted deleted file move/copy it to temp file
    while(fgets(buffer, 255, main_file))
    {
            
        if(line_no != count)
        {
            fprintf(temp_file,"%s", buffer);
        }
        count++;
    }


    // delete the main file
    fclose(main_file);
    remove("database.txt");
    printf("Removing File...");    

    // rename the temp file to main file
    fclose(temp_file);
    rename("___temp.txt", "database.txt");

    // exit (freed the used allocated memory and flush stream input)
    fflush(stdin);
    free(buffer);
    Sleep(1500);
}