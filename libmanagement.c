#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // clear-screen
#include <string.h>
// #include "structs.c" // contains all the structs used 
#include "books.c"  // contain functions that involves the books
#include "students.c"  // contains all functions that involve the book


void menu (void);
void time2(void);
void user(void);
void login (void);

// main function: the program starts executing here
int main (void) 
{
    system("clear");
    int choice;
    puts("\v\v\v\t\t\t\t\t\t\t\t\t```````````````````````````````````````` ");
    puts("\t\t\t\t\t\t\t\t\t\t\033[22;34mLIBRARY MANAGEMENT SYSTEM\033[0m");
    puts("\t\t\t\t\t\t\t\t\t```````````````````````````````````````` \v\v\v\v\v\v");

    puts("\v\v\t\t\t\t\t\t***********************************************************************************************\n"
            "\t\t\t\t\t\t\t\t|1| log in       \t\t|2|  Forgot password?\n"
            "\t\t\t\t\t\t************************************************************************************************\n\v"
            "\t\t\t\t\t\t________________________________________________________________________________________________\n\n"
            "\t\t\t\t\t\t\t\t\t\t|3| register\n"          
            "\t\t\t\t\t\t________________________________________________________________________________________________\n"            
            );
    
    time2();

    printf("%s", "\v\t\t\t\t\t\t\t\t\t(Enter your choice here)->\t");
    scanf("%d", &choice);
    
    switch (choice)
    {
        case 1:
            login();
            break;
        case 3:
            addStudent();
            break;
    
        default:
            main();
            break;
    }     
}

void login(void)
{
    system("clear");
    puts("\v\v\v\t\t\t\t\t\t\t\t\t```````````````````````````````````````` ");
    puts("\t\t\t\t\t\t\t\t\t\t\033[22;34mLOG IN\033[0m");
    puts("\t\t\t\t\t\t\t\t\t```````````````````````````````````````` \v\v\v\v\v\v");

    int choice;
    puts("\v\v\t\t\t\t\t\t***********************************************************************************************\n"
            "\t\t\t\t\t\t\t\t|1| Librarian       \t\t|2|  Student\n"
            "\t\t\t\t\t\t************************************************************************************************\v\n"
            "\t\t\t\t\t\t_______________________________________________________________________________________________\n"
            "\t\t\t\t\t\t\t\t\t\t|o| Log Out\n"
            "\t\t\t\t\t\t_______________________________________________________________________________________________\n"
            );

        time2();

    printf("%s", "\v\t\t\t\t\t\t\t\t\t(Enter your choice here)->\t");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            menu();

            break;
        case 2:
            user();
            break;
        default:
            main();
            break;
    }

}

void user(void)
{
    system("clear");    // works only for linux sys (windows system("cls"))

    int choice;
    puts("\v\v\v\t\t\t\t\t\t\t\t\t```````````````````````````````````````` ");
    puts("\t\t\t\t\t\t\t\t\t\t\033[22;34mLIBRARY MANAGEMENT SYSTEM\033[0m");
    puts("\t\t\t\t\t\t\t\t\t```````````````````````````````````````` \v\v\v\v\v\v");

    puts("\v\v\t\t\t\t\t\t***********************************************************************************************\n"
        "\t\t\t\t\t\t\t\t|1| View Books       \t\t|3|  Account Details\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"
        "\t\t\t\t\t\t\t\t|2| Search Book          \t\t|4|  Update details\n"
        "\t\t\t\t\t\t***********************************************************************************************\n"
        "\t\t\t\t\t\t_______________________________________________________________________________________________\n"
        "\t\t\t\t\t\t\t\t\t\t|o| Log Out"
        "\t\t\t\t\t\t_______________________________________________________________________________________________\n"
        );

         time2();
        // puts("\v\t\t******************************");
        printf("%s", "\v\t\t\t\t\t\t\t\t\t(Enter your choice here)->\t");
        scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            viewBooks();
            break;
        case 2:
            searchBook();
            break;
        case 3:
            // searchStudent();
            break;
        case 4:
            updateStudent();
            break;
    
        default:
            main();
            break;
    }    
}


void time2(void)
{
    time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        printf("\v\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tTime is: %d:%d:%d\ton: %d-%d-%d \n", 
            tm.tm_hour, tm.tm_min, tm.tm_sec,
            tm.tm_mday, tm.tm_mon,tm.tm_year + 1900);
}




// admin view 
void menu(void)
{
    system("clear");    // works only for linux sys

    int choice;
    puts("\v\v\v\t\t\t\t\t\t\t\t\t```````````````````````````````````````` ");
    puts("\t\t\t\t\t\t\t\t\t\t\033[22;34mLIBRARY MANAGEMENT SYSTEM\033[0m");
    puts("\t\t\t\t\t\t\t\t\t```````````````````````````````````````` \v\v\v\v\v\v");

    puts("\v\v\t\t\t\t\t\t***********************************************************************************************\n"
        "\t\t\t\t\t\t\t\t|1| Add student       \t\t|7|  update book\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"
        "\t\t\t\t\t\t\t\t|2| add Book          \t\t|8|  delete book\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"
        "\t\t\t\t\t\t\t\t|3| search for a Book \t\t|9| return book\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"        
        "\t\t\t\t\t\t\t\t|4| view books        \t\t|10| delete student\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"
        "\t\t\t\t\t\t\t\t|5| issue book        \t\t|11| update student\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"        
        "\t\t\t\t\t\t\t\t|6| view issued book  \t\t|12| view student\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"        
        "\t\t\t\t\t\t\t\t|0| Log Out\n   "
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
        main();
        break;
    }

}