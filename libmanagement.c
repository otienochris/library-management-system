#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // clear-screen
#include <string.h>
#include "structs.c" // contains all the structs used 
#include "books.c"  // contain functions that involves the books
#include "students.c"  // contains all functions that involve the book


void menu (void);

// main function: the program starts executing here
int main (void) 
{

    menu();
}


void menu(void)
{
    system("clear");    // works only for linux sys

    int choice;

    puts("\v\v\t\t1 -> Add student\n"
        "\t\t2 -> add Book\n"
        "\t\t3 -> search for a Book\n"
        "\t\t4 -> view books\n"
        "\t\t5 -> exit the program");
    printf("%s", "\v\t\t>");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        addStudent();
        break;
    case 2:
        // validatedBookId();
        addBook();
        break;
    case 3:
        searchBook();
        break;
    case 4:
        viewBooks();
        break;
    case 5:
        puts("\v\t\tThanks for spending time here.");
        puts("\t\tjust a minute ... \n");
        sleep(2);
        exit(1);

    default:
        puts("Invalid entry");

        menu();
        break;
    }

}