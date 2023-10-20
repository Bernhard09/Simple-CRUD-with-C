#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "util.h"


void tampilkanMenu();


int main(int argc, char const *argv[])
{   
    // declaration
    char userInput;


    do
    {
        system("cls");    

        // tampilkan menu
        tampilkanMenu(); 

        // input user
        do
        {   
            fflush(stdin);
            printf("Pilih opsi: ");
            scanf("%c", &userInput);
        }
        while (userInput < 48 || userInput > 52);

        switch (userInput)
        {
        case '1':
            createInfo();
            break;
        case '2':
            fflush(stdin);
            readInfo();
            char isContinue;
            printf("Press enter to continue: ");
            scanf("%c", &isContinue);    
            Sleep(1500);
            break;
        case '3':
            fflush(stdin);
            updateInfo();
            char isCont;
            printf("Press enter to continue: ");
            scanf("%c", &isCont);    
            Sleep(1500);
            break;
        case '4':
            deleteInfo();
            break;
        case '0':
            printf("Anda memilih keluar dari program...\n");
            break;
        default:
            printf("Invalid Input\n");
            break;
        }

    } while (userInput != '0');

    Sleep(1500);
    return 0;
}


void tampilkanMenu()
{
    printf("\n======================\n");
    printf("MANAJEMEN PERPUSTAKAAN\n");
    printf("======================\n\n");
    printf("1. Tambah Informasi\n----------------------\n");
    printf("2. Baca Informasi\n----------------------\n");
    printf("3. Perbarui Informasi\n----------------------\n"); 
    printf("4. Hapus Informasi\n----------------------\n");
    printf("0. Keluar\n\n");
}