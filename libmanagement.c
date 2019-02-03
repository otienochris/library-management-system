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

    puts("\v\v\t\t***********************\n"
        "\t\t1 -> Add student\n"
        "\t\t***********************\n"
        "\t\t2 -> add Book\n"
        "\t\t***********************\n"
        "\t\t3 -> search for a Book\n"
        "\t\t***********************\n"
        "\t\t4 -> view books\n"
        "\t\t***********************\n"
        "\t\t5 -> issue book\n"
        "\t\t***********************\n"
        "\t\t6 -> view issued book\n"
        "\t\t***********************\n"
        "\t\t7 -> view students\n"
        "\t\t***********************\n"
        "\t\t8 -> exit the program\n"
        "\t\t***********************\n"
        );
    // puts("\v\t\t******************************");
    printf("%s", "\v\t\t(Enter your choice here)->\t");
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
        issueBook();
        break;
    case 6:
        viewIssuedBook();
        break; 
    case 7:
        viewStudents();
        break;
    case 8:
        system("clear");

        puts("\v\v\v\v\t\t\tloading...");
        sleep(3);
        system("clear");

        puts("\v\v\v\v\t\t\t\tjust a second (saving changes)... \n");
        sleep(2);
        system("clear");

        puts("\v\v\v\v\t\t\t\t\t\tDone...BYE!\n");
        sleep(2);
        system("clear");
        
        exit(1);

    default:
        puts("Invalid entry");
        break;
    }
    menu();

}