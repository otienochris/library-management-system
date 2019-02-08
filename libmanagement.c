#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // clear-screen
#include <string.h>
// #include "structs.c" // contains all the structs used 
#include "books.c"  // contain functions that involves the books
#include "students.c"  // contains all functions that involve the book

typedef struct
{
    // COURSE course;
    // DATE dob;
    unsigned int day, id, month, year ;
    char  fname[30], lname[30];
    char faculty[30], department[30], course_title[30];
} STUDENT3;

FILE *studentPtr;

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

    puts("\v\v\t\t\t\t\t\t************************************************************************************************\n"
            "\t\t\t\t\t\t\t\t|1| Log In       \t\t\t|2| Forgot Password?\n"
            "\t\t\t\t\t\t************************************************************************************************\n\v\v"
            "\t\t\t\t\t\t************************************************************************************************\n"
            "\t\t\t\t\t\t\t\t|3| Register     \t\t\t|0| Exit\n"          
            "\t\t\t\t\t\t************************************************************************************************\n\v"
            
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
            main();
            break;
    
        default:
            system("clear");

            puts("\v\v\v\v\t\t\t\tjust a second (saving changes)... \n");
            sleep(2);
            system("clear");

            puts("\v\v\v\v\t\t\t\t\t\tDone...BYE!\n");
            sleep(1);
            system("clear");
            exit(1);
            break;
    }     
}

void login(void)
{
    system("clear");
    puts("\v\v\v\t\t\t\t\t\t\t\t\t```````````````````````````````````````` ");
    puts("\t\t\t\t\t\t\t\t\t\t\t\033[22;34mLOG IN\033[0m\n");
    puts("\t\t\t\t\t\t\t\t\t```````````````````````````````````````` \v\v\v\v\v\v");

    int choice;
    puts("\v\v\t\t\t\t\t\t***********************************************************************************************\n"
            "\t\t\t\t\t\t\t\t|1| Librarian       \t\t\t\t|2|  Student\n"
            "\t\t\t\t\t\t***********************************************************************************************\v\v\v\n"
            "\v\v\t\t\t\t\t\t_______________________________________________________________________________________________\n\n"
            "\t\t\t\t\t\t\t\t\t\t\t|0| Exit\n"
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
            system("clear");
            puts("\t\t\t\t\t\t\t\t\t\t\t\033[22;34mSTUDENT LOG IN\033[0m\n");

            studentPtr = fopen("student.dat", "rb+");
            if (studentPtr == NULL) {
                puts("Error: Could not open the files ");
            }
            else
            {  
                unsigned int student_id;
                char student_fname[30], stop = 'n';

                printf("\v\v\t\t\t\tEnter your id and your first name (e.g 35879912 otieno)\t\t->\t");
                scanf("%u%s", &student_id,student_fname);
                while(!feof(studentPtr) && stop == 'n')
                {
                    STUDENT3 student;
                    fread(&student, sizeof(STUDENT3), 1, studentPtr);
                
                    if (student_id == student.id && strcmp(student_fname,student.fname) == 0 ) 
                    {
                        // int SIZE = 30;
                        stop = 'y';// stop the search of the student
                        user(); // custom for the users
                    }
                }

                // error message if student is not registered
                if (stop == 'n') {
                    puts("\v\v\v\t\t\t_______________________________________________________________________________________________\n");
                    puts("\t\t\t\tError: You need to register first to log into the system ");
                    puts("\t\t\t_______________________________________________________________________________________________\n\n");

                    sleep(3);
                    main();
                }
            fclose(studentPtr);
            
            }
            break;
        default:
            main();
            break;
    }

}

void user()
{
    system("clear");    // works only for linux sys (windows system("cls"))

    int choice;
    puts("\v\v\v\t\t\t\t\t\t\t\t\t```````````````````````````````````````` ");
    puts("\t\t\t\t\t\t\t\t\t\t\033[22;34mLIBRARY MANAGEMENT SYSTEM\033[0m\v");
    puts("\t\t\t\t\t\t\t\t\t```````````````````````````````````````` \v\v\v\v\v\v");

    puts("\v\v\t\t\t\t\t\t***********************************************************************************************\n"
        "\t\t\t\t\t\t\t\t|1| View Books           \t\t|3|  Account Details\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"
        "\t\t\t\t\t\t\t\t|2| Search Book          \t\t|4|  Update details\n"
        "\t\t\t\t\t\t***********************************************************************************************\v\v\v\n"
        "\v\v\v\v\t\t\t\t\t\t_______________________________________________________________________________________________\n\n"
        "\t\t\t\t\t\t\t\t\t\t|0| Log Out\n"
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
            user();
            break;
        case 2:
            searchBook();
            user();
            break;
        case 3:
            // searchStudent();
            break;
        case 4:
            updateStudent();
            user();
            break;
    
        default:
            // main();
            break;
    }
    main();    
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
        "\t\t\t\t\t\t\t\t|3| search for a Book \t\t|9|  return book\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"        
        "\t\t\t\t\t\t\t\t|4| view books        \t\t|10| delete student\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"
        "\t\t\t\t\t\t\t\t|5| issue book        \t\t|11| update student\n"
        "\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````````````````\n"        
        "\t\t\t\t\t\t\t\t|6| view issued book  \t\t|12| view student\n"
        "\t\t\t\t\t\t***********************************************************************************************\n"
        "\v\v\t\t\t\t\t\t_______________________________________________________________________________________________\n\n"
        "\t\t\t\t\t\t\t\t\t\t|0| Log Out\n   "
        "\t\t\t\t\t\t_______________________________________________________________________________________________\n"
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
        menu();
        break;
    case 2:
        // validatedBookId();
        addBook();
        menu();
        break;
    case 3:
        searchBook();
        menu();
        break;
    case 4:
        viewBooks();
        menu();
        break;
    case 5:
        issueBook();
        menu();
        break;
    case 6:
        viewIssuedBook();
        menu();
        break; 
    case 7:
        updateBook();
        menu();
        break;
    case 8:
        deleteBook();
        menu();
        break;
    case 9:
        returnBook();
        menu();
        break;
    case 10:
        deleteStudent();
        menu();
        break;
    case 11:
        updateStudent();
        menu();
        break;
    case 12:
        viewStudents();
        menu();
        break;
    default:
        puts("Invalid entry");
        menu();
        break;
    }

}

