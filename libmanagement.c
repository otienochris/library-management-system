#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "structs.c"
#include "functions.c"


void menu (void);
int main (void) 
{

    menu();
}


void menu(void)
{
    system("clear");    // works only for linux sys

    int choice;

    puts("1 -> Add student\n"
        "2 -> add Book\n"
        "3 -> search for a Book\n"
        "4 -> view books\n"
        "5 -> exit the program");
    printf("%s", ">");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        addStudent();
        break;
    case 2:
        addBook();
        break;
    case 3:
        searchBook();
        break;
    case 4:
        viewBooks();
        break;
    case 5:
        puts("Thanks for spending time here.");
        puts("just a minute ... ");
        sleep(2);
        exit(1);

    default:
        puts("Invalid entry");

        menu();
        break;
    }

}