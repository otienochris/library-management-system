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

typedef struct 
{
    char fname[40], lname[40], username[40], password[60];
}   ADMIN;


FILE *studentPtr;

void menu (void);
void time2(void);
void user(void);
void login (void);
void addAdmin(void);
void viewAdmin(void);
void deleteAdmin(void);

// main function: the program starts executing here
int main (void) 
{
    system("clear");
    int choice;
    puts("\v\v\v\t\t\t\t\t\t\t\t\t```````````````````````````````````````` ");
    puts("\t\t\t\t\t\t\t\t\t\t\033[22;34mLIBRARY MANAGEMENT SYSTEM\033[0m");
    puts("\t\t\t\t\t\t\t\t\t```````````````````````````````````````` \v\v\v\v\v\v");

    puts("\v\v\t\t\t\t\t\t************************************************************************************************\n"
            "\t\t\t\t\t\t\t\t|1| Log In       \t\t\t|2| Forgot ID?\n"
            "\t\t\t\t\t\t************************************************************************************************\n\v\v"
            "\t\t\t\t\t\t************************************************************************************************\n"
            "\t\t\t\t\t\t\t\t|3| Register     \t\t\t|0| Exit\n"          
            "\t\t\t\t\t\t************************************************************************************************\n\v"
            
            );
    
    time2();

    printf("%s", "\v\t\t\t\t\t\t\t\t\t(Enter your choice here)->\t");
    scanf("%d", &choice);
    int SIZE = 40;
    
    switch (choice)
    {
        case 1:
            login();
            break;
        case 2:
            printf("\v\v\t\t\t\t\t\tEnter your last name and your date of birth\n\t\t\t\t\t\t(eg otieno (day) (month) (year) i.e 12 12 1998)\t\t->\t");
            char lname[40]; unsigned int day,month,year;
            scanf("%39s%u%u%u", lname, &day, &month, &year);
            passReset(SIZE, lname, day, month, year);
            main();
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
            system("clear");
            puts("\t\t\t\t\t\t\t\t\t\t\t\033[22;34mLIBRARIAN LOG IN\033[0m\n");

            userPtr = fopen("admin.dat", "rb+");
            if (userPtr == NULL) {
                puts("Error: The admin file could not be opened");
            }
            else
            {
                char stop_search = 'n', user_name[40], pass_word[60];

                printf("\v\v\t\t\tEnter your username and password \t\t->\t");
                scanf("%39s%59s", user_name, pass_word);

                while(!feof(userPtr) && stop_search == 'n')
                {
            
                    ADMIN admin;
                    int result = fread(&admin, sizeof(ADMIN), 1, userPtr);
                    if (result != 0 && strcmp(admin.username,user_name) == 0 && strcmp(admin.password, pass_word) == 0) 
                    {
                        stop_search = 'y'; // allow the loop containing the menu() to execute
                        fclose(userPtr);
                    }
                }

                if(stop_search == 'y'){
                    menu();                
                }
                else
                {
                    printf("\v\v\v\t\t\t_______________________________________________________________________________________________\n");
                    printf("\t\t\t\tError: Wrong cridentials. \n");
                    printf("\t\t\t_______________________________________________________________________________________________\n\n");
                    sleep(2);
                    login();
                }  

            }

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
                    printf("\v\v\v\t\t\t_______________________________________________________________________________________________\n");
                    printf("\t\t\t\tError: You need to register first to log into the system \n");
                    printf("\t\t\t_______________________________________________________________________________________________\n\n");

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

void user(void)
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
        int SIZE = 40;

    switch (choice)
    {
        case 1:
            // viewAdmin();
            // addAdmin();
            viewBooks();
            user();
            break;
        case 2:
            searchBook();
            user();
            break;
        case 3:
            system("clear");
            puts("\v\v\v\t\t\t\t\t\t\t\t\t```````````````````````````````````````` ");
            puts("\t\t\t\t\t\t\t\t\t\t\033[22;34mCONFIRM YOUR DETAILS\033[0m\v");
            puts("\t\t\t\t\t\t\t\t\t```````````````````````````````````````` \v\v\v\v\v\v");

            printf("\v\v\t\t\tEnter your id and fname\t\t->\t");
            unsigned int id; char fname[40];
            scanf("%u%39s", &id, fname);
            accountDetails(SIZE, id, fname);
            user();
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
        "\t\t\t\t\t\t\t\t|1| Search student    \t\t|7|  update book\n"
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
        "\t\t\t\t\t\t\t|-1| Add admin\t\t|-2| View Admins\t|-3| Delete Admin\t|0| Exit\n"
        // "\t\t\t\t\t\t\t\t\t\t|0| Exit\n   "
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
        searchStudent();
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
    case -1:
        addAdmin();
        menu();
        break;
    case -2:
        viewAdmin();
        // sleep(3);
        menu();
        break;
    case -3:
        deleteAdmin();
        // sleep(3);
        menu();
        break;
    case 0:
        // puts("Bye");
        main();
        break;
    default:
        puts("Invalid entry");
        sleep(2);
        menu();
        break;
    }

}

void addAdmin(void)
{
    system("clear");
    puts("\v\v\v\t\t\t\t\t\t\t\t\t```````````````````````````````````````` ");
    puts("\t\t\t\t\t\t\t\t\t\t\033[22;34mADD ADMIN\033[0m");
    puts("\t\t\t\t\t\t\t\t\t```````````````````````````````````````` \v\v\v\v\v\v");
    userPtr = fopen("admin.dat", "a+");

    if (userPtr == NULL) {
        puts("Error: Could not open the admin the file ");
    }
    else
    {
        ADMIN admin;

        // char user_name[40];
        char dont_save = 'n';

        printf("\v\v\t\t\tEnter your first name and your last name (eg otieno chris) ->\t");
        scanf("%39s%39s", admin.fname, admin.lname);

        printf("\v\v\t\t\tEnter the username and passworsd (eg chrisly s13/09426@17) ->\t");
        scanf("%39s%59s", admin.username, admin.password);
        // admin.username = user_name;
        // while(!feof(userPtr) && dont_save == 'n')
        // {
        //     fread(&admin, sizeof(ADMIN), 1, userPtr);
        //     if (strcmp(admin.username, user_name) == 0) {
        //         puts("Error: The username exists!");
        //         dont_save = 'y';
        //     }
        // }

        if(dont_save == 'n'){
            fwrite(&admin, sizeof(ADMIN), 1, userPtr);
            puts("Record successfully saved");
            fclose(userPtr);
        }
            
        
    }
}

void viewAdmin(void)
{
    system("clear");
    puts("\v\v\v\t\t\t\t\t\t\t\t\t```````````````````````````````````````` ");
    puts("\t\t\t\t\t\t\t\t\t\t\033[22;34mVIEW ADMIN\033[0m");
    puts("\t\t\t\t\t\t\t\t\t```````````````````````````````````````` \v\v\v\v\v\v");
    userPtr = fopen("admin.dat", "rb+");

    if (userPtr == NULL) {
        puts("Error: Could not open the admin the file ");
    }
    else
    {
            puts("\v\v\t\t\t\t\t\t\t First_name\t\t\t     Last_name\t\t\t          User_name");
            puts("\t\t\t\t\t\t\t_______________________________________________________________________________________\v");
        while(!feof(userPtr)){
            // puts("was here");
            ADMIN admin;
            int result = fread(&admin, sizeof(ADMIN), 1, userPtr);
            if (result != 0 ) {
                printf("\t\t\t %39s%39s%39s\n", admin.fname, admin.lname, admin.username);
                puts("\t\t\t\t\t\t\t````````````````````````````````````````````````````````````````````````````````````````");

            }
        }
        puts("\v\t\t\t\t\t\t\t_______________________________________________________________________________________\v");

        fclose(userPtr);

        puts("\v\v\v\v\v\v\v\t\t\t\t\t\t##########################################################################################");
        printf("\t\t\t\t\t\tEnter 0 to go back to the main menu");
        printf("%s", "\t\t(Enter your choice here)->\t");
        int choice;
        scanf("%d", &choice);

        if (choice == 0)
        {
            // go to the customized view
        }
        
    }
}

void deleteAdmin(void)
{

    system("clear");
    puts("\v\v\v\t\t\t\t\t\t\t\t\t```````````````````````````````````````` ");
    puts("\t\t\t\t\t\t\t\t\t\t\033[22;34mDELETE ADMIN\033[0m");
    puts("\t\t\t\t\t\t\t\t\t```````````````````````````````````````` \v\v\v\v\v\v");
    userPtr = fopen("admin.dat", "rb+");

    if (userPtr == NULL) {
        puts("Error: Could not open the admin the file ");
    }
    else
    {
        ADMIN admin;
        int count = 0;
        printf("\t\t\tEnter the username of the admin you wish to delete\t->\t");
        char user_name[40], stop_search = 'n';
        scanf("%39s", user_name);

        while(!feof(userPtr) && stop_search == 'n')
        {
            int result = fread(&admin, sizeof(ADMIN), 1, userPtr);
            count += result; // keeps track of the record we are at

            if (strcmp(user_name, admin.username)==0 && result != 0) {
                puts("\v\v\v\v\t\t\t________________________________________________________________________________________\n");
                printf("\t\t\tRecord to be deleted ->%39s%39s%39s\n",  admin.fname, admin.lname, admin.username); 
                puts("\t\t\t________________________________________________________________________________________");
                
                // confirm of deletion
                int confirm;
                printf("\v\v\v\t\t\tConfirm deletion by entering 1 otherwise 0 (then press enter key)\t\t ->\t");
                scanf("%d", &confirm);

                if (confirm == 1) 
                {   puts("\v\v\v\v\t\t\t________________________________________________________________________________________");
                    puts("\n\t\t\t\t\t\tHurray: Record is successfully deleted ");
                    puts("\t\t\t________________________________________________________________________________________");
                
                // set the cursor to the begining of the right record
                fseek(userPtr, (count -1)*sizeof(ADMIN), SEEK_SET);
                fread(&admin, sizeof(ADMIN), 1, userPtr);
                
                ADMIN blankadmin = {"", "", "", ""};
                
                // place the cursor back to the beginning of the deleted record's space
                fseek(userPtr, (count -1)*sizeof(ADMIN), SEEK_SET);
                fwrite(&blankadmin, sizeof(ADMIN), 1, userPtr);
                }
                else
                {
                    puts("\v\v\v\v\t\t\t________________________________________________________________________________________");
                    printf("\t\t\t\tRetained record -> \t%39s%39s%39s\n\n",admin.fname, admin.lname, admin.username);  
                    puts("\t\t\t________________________________________________________________________________________");
                      
                }

                stop_search = 'y';
            }
            
        }
        fclose(userPtr);
        puts("\v\v\v\v\v\v\v\t\t\t\t\t##########################################################################################");
        printf("\t\t\t\t\t\tEnter 0 to go back to the main menu");
        printf("%s", "\t\t(Enter your choice here)->\t");
        int choice;
        scanf("%d", &choice);

        if (choice == 0)
        {
            // go to the customized view
        }
    }
}