#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // clear-screen
#include <string.h>
// #include "structs.c" // contains all the structs used 
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
    puts("\v\v\v\t\t\t\t\t\t\t\t\t```````````````````````````````````````` ");
    puts("\t\t\t\t\t\t\t\t\t\t\033[22;34mLIBRARY MANAGEMENT SYSTEM\033[0m");
    puts("\t\t\t\t\t\t\t\t\t```````````````````````````````````````` \v\v\v\v\v\v");

    puts("\v\v\t\t\t\t\t\t***********************************************************************************************\n"
        "\t\t\t\t\t\t\t\t|1| Add student       \t\t|8|  update book\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"
        "\t\t\t\t\t\t\t\t|2| add Book          \t\t|9|  delete book\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"
        "\t\t\t\t\t\t\t\t|3| search for a Book \t\t|10| return book\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"        
        "\t\t\t\t\t\t\t\t|4| view books        \t\t|11| delete student\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"
        "\t\t\t\t\t\t\t\t|5| issue book        \t\t|12| update student\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"        
        "\t\t\t\t\t\t\t\t|6| view issued book  \t\t|13| exit the program\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"        
        "\t\t\t\t\t\t\t\t|7| view students\n   "
        "\t\t\t\t\t\t***********************************************************************************************\n"
        );

        time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\v\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tTime is: %d:%d:%d\ton: %d-%d-%d \n", 
        tm.tm_hour, tm.tm_min, tm.tm_sec,
        tm.tm_mday, tm.tm_mon,tm.tm_year + 1900); 
    // puts("\v\t\t******************************");
    printf("%s", "\v\t\t\t\t\t\t\t\t\t(Enter your choice here)->\t");
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
        updateBook();
        break;
    case 9:
        deleteBook();
        break;
    case 10:
        returnBook();
        break;
    case 11:
        deleteStudent();
        break;
    case 12:
        updateStudent();
        break;
    case 13:
        /* system("clear");

        puts("\v\v\v\v\t\t\tloading...");
        sleep(3); */
        system("clear");

        puts("\v\v\v\v\t\t\t\tjust a second (saving changes)... \n");
        sleep(2);
        system("clear");

        puts("\v\v\v\v\t\t\t\t\t\tDone...BYE!\n");
        sleep(1);
        system("clear");
        
        exit(1);

    default:
        puts("Invalid entry");
        menu();
        break;
    }

}