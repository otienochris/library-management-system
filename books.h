#include <stdio.h>
#include <time.h>

void suggestBook(void);
int leapYear (int year);

void boro_return_date(int day, int month, int year, int *r_d, int *r_m, int *r_y);

// borrow return dates
typedef struct 
{
    int b_day, b_month, b_year; // borrowed day,month,year
    int r_day, r_month, r_year; // return day,month,year
}DATE;

// struct used to store issuedbook info
typedef struct
{
    unsigned int student_id, book_id;
    DATE date;
} ISSUEDBOOK;

// struct to store book info
typedef struct
{
    unsigned int id, copies, rack, pub_year;
    char title[30], author[30], publisher[30], edition[5];
} BOOK;

// struct used to student info
typedef struct
{
    unsigned int day, id, month, year ;
    char  fname[30], lname[30];
    char faculty[30], department[30], course_title[30];
} STUDENT;

void menu(void);
void searchissued(void);

//  global pointers (set to null to avoid segmentation faults)
FILE *bookPtr = NULL, *studentPtr = NULL, *userPtr = NULL , *issuedBookPtr = NULL;

// global struct declaration
STUDENT student;
ISSUEDBOOK issuedbook;

// a function that adds a book(s) to books.dat file    
void addBook(void)
{
    system("clear"); // works on linux (comment this line while using windows)
    // system("cls")  // uncomment this line while on windows

    unsigned int book_id; // to hold the id temporarily for verification

    // initial book struct
    BOOK book;

    // open the books file
    bookPtr = fopen("books.dat", "a+");

    puts("\v\t\t\t\t\t\t\t\t````````````````````````````````");
    puts("\t\t\t\t\t\t\t\t\t   \033[22;34mADD BOOK\033[0m\n");
    puts("\t\t\t\t\t\t\t\t````````````````````````````````\v\v");

    puts("\v\v\v\v\t\t\t________________________________________________________________________________________\n");
    printf("%s", "\n\t\t\t N/B:Enter 0 as book id to exit: \n");
    puts("\t\t\t________________________________________________________________________________________");

    // enter id for verification
    printf("%s", "\v\v\t\t\tEnter book id: \t\t->\t");
    scanf("%u", &book_id);
        
    // scan the books records to check if the id exist       
    while (!feof(bookPtr))
    {
        fread(&book, sizeof(BOOK), 1, bookPtr);
        if (book_id == book.id)
        {
            puts("\v\v\v\v\t\t\t________________________________________________________________________________________");
            puts("\t\t\t\tError: The book id exists");
            puts("\t\t\t________________________________________________________________________________________");
            sleep(2);
            book_id = 0 ; // 
        }
    }



    // if book does not exist, enter the records of the new book
    if( book_id != 0 )
    {
        // initialize book.id with the entered book_id
        book.id = book_id;

        puts("\v\v\t\t\t---------------------------------------------------------------------------------------------------");
        puts("\n\t\t\tNB:\tMultiple names must be separated using a hyphen(eg c-programming otieno-chris 900)");
        puts("\n\t\t\t---------------------------------------------------------------------------------------------------");
        printf("%s", "\n\v\t\t\tEnter title, author, publisher and edition. (e.g c-programming christopher Longhorn 4th )\t>\t");
        scanf("%29s%29s%29s%9s", book.title, book.author, book.publisher, book.edition);

        printf("%s", "\n\v\t\t\tEnter publication_year, copies and rack_number. (e.g 2013 20 122 )\t\t\t\t>\t");
        
        unsigned int rack, pub_year;
        signed int copies;
        scanf("%u%u%u",&pub_year,&copies, &rack );
        book.rack = rack;

        
        while (copies < 1  ) {
            puts("\v\t\t\tEnter a value greater than zero for the copies!");
            printf("\t\t\t->\t");
            scanf("%u", &copies);
        }

        book.copies = copies;
    
        book.pub_year = pub_year;
        

      
        fwrite(&book, sizeof(BOOK), 1, bookPtr);
        printf("%s", "\n\v\t\t\tRecords saved successfully\t>\t");
        
        
        

    }

    fclose(bookPtr); // close the books file
                
    // navigation: continue or exit
    puts("\v");

    int choice;
    puts("\v\v\v\v\v\v\v\t\t\t##########################################################################################");
    printf("\t\t\tEnter 0 to go back to the main menu (1 to continue)");
    printf("%s", "\t\t(Enter your choice here)->\t");

    scanf("%u", &choice);

    // go back to the same function        
    if (choice == 1)
    {
        addBook();
    }
    // exit to the main menu
    else
    {

        printf("%s", "\v\t\tloading...\n");
    }



}

// search for a book
void searchBook(void)
{
    system("clear"); // works on linux (comment this line while using windows)
    // system("cls")  // uncomment this line while on windows

    puts("\v\t\t\t\t\t\t\t\t\t\t````````````````````````");
    puts("\t\t\t\t\t\t\t\t\t\t\t\033[22;34mSEARCH BOOK\033[0m");
    puts("\t\t\t\t\t\t\t\t\t\t........................\v\v\v\v");
    bookPtr = fopen("books.dat", "rb+");

    if (bookPtr == NULL)
    {
        puts("Error opening the book information file");
    }
    else
    {
        unsigned int search_id;
        char search_title[30], done_search = 'n';
        int choice;

        printf("%s", "\v\t\t\t\t\t\t________________________________________________________________________________________\n\n"
                "\t\t\t\t\t\t\t|1| Search by title\t\t<-- or -->\t\t|2| Search by id\n"
                "\t\t\t\t\t\t________________________________________________________________________________________\n"
                "\n\t\t\t\t\t\t\t\t|3|Not sure of the book title or id? get suggestions "
                "\n\t\t\t\t\t\t________________________________________________________________________________________\n"
                );
        printf("%s", "\v\v\t\t\t\t\t\t(Enter your choice here)\t\t\t\t->\t");

        scanf("%d", &choice);

        switch(choice){
            case 1:

                printf("%s","\v\v\n\t\t\t\t\t\tEnter the title of the book to search:\t\t\t->\t");
                scanf("%29s", search_title);

                puts("\v\v\t\t\t_____________________________________________________________________________________________________________________________________________________");    
                puts("\v\t\t\tBook_id\t\tTitle\t\t\tAuthor\t\t\t\t    publisher\t\t\tedition\t   pub_year\tCopies\t  Rack_no.");
                puts("\t\t\t_____________________________________________________________________________________________________________________________________________________");

                while ( !feof(bookPtr) && done_search == 'n')
                {
                    BOOK book;
                    int  result = fread(&book, sizeof(BOOK), 1, bookPtr);

                   // searches a book that has a title containing the title entered 
                    if ( (strcmp(book.title, search_title) == 0) && (result != 0) )
                        {
                        
                            printf("\n\t\t\t%-10u %-29s%-39s%-29s%-10s%-4u\t%-10u%-10u\n", book.id, book.title, book.author, book.publisher, book.edition,book.pub_year, book.copies, book.rack);
                            puts("\t\t\t`````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````");

                            // if copies are zero then provide suggestion by title or author of other books in the lib
                            if (book.copies == 0) 
                            {
                                int choice;

                                puts("\v\v\v\t\t\t\t\t\t________________________________________________________________________________________\v");
                                printf("\t\t\t\t\t\t Enter 1 to get suggestion or 0 to continue\t\t->\t");
                                scanf("%d", &choice);
                                fflush(stdin);
                                if (choice == 1) 
                                    suggestBook();
                                
                            }
                            done_search = 'y';                          
                        }
                }
                        
                fclose(bookPtr); // close the file
                
                break;

            case 2:
                
                printf("%s","\v\v\n\t\t\t\t\t\tEnter the id of the book to search:\t\t\t->\t");
                // printf("%s", "\v\t\t(Enter the title here)->\t");
                scanf("%d", &search_id);

                puts("\v\v\t\t\t_____________________________________________________________________________________________________________________________________________________");    
                puts("\v\t\t\tBook_id\t\tTitle\t\t\tAuthor\t\t\t\t    publisher\t\t\tedition\t   pub_year\tCopies\t  Rack_no.");
                puts("\t\t\t_____________________________________________________________________________________________________________________________________________________");

                while (!feof(bookPtr) && done_search == 'n')
                {
                    BOOK book;
                    int  result = fread(&book, sizeof(BOOK), 1, bookPtr);
                    if ( (result != 0) &&  book.id == search_id  )
                        {
                            printf("\n\t\t\t%-10u %-29s%-39s%-29s%-10s%-4u\t%-10u%-10u\n", book.id, book.title, book.author, book.publisher, book.edition,book.pub_year, book.copies, book.rack);
                            puts("\t\t\t`````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````");

                             // if copies are zero then provide suggestion by title or author of other books in the lib
                            if (book.copies == 0) 
                            {
                                int choice;
                                printf("\v\v\t\t\t\t\t\t Enter 1 to get suggestion or 0 to continue\t\t->\t");
                                scanf("%d", &choice);
                                fflush(stdin);
                                if (choice == 1) 
                                    suggestBook();
                                
                            };
                            done_search = 'y';
                        }

                }

                fclose(bookPtr); // close the file
                break;
            case 3:
                // a function that suggest for a book using few key characters
                suggestBook();
                break;


        }
                puts("\v");

                int choice2;
                puts("\v\v\v\v\v\v\v\t\t\t\t\t\t##########################################################################################");
                printf("\t\t\t\t\t\tEnter 0 to go back to the main menu");
                printf("%s", "\t\t(Enter your choice here)->\t");

                scanf("%u", &choice2);

                if (choice2 == 0)
                {
                    // go to the customized view                    
                }
    }
}

// a function that returns all the books' inventory
void viewBooks(void)
{
    system("clear"); // works on linux (comment this line while using windows)
    // system("cls")  // uncomment this line while on windows
    
    puts("\v\t\t\t\t\t\t\t\t\t\t\t\033[22;34mLIST OF BOOKS\033[0m");
    puts("\t\t\t\t\t\t\t\t\t\t`````````````````````````````");
    
    bookPtr = fopen("books.dat", "rb");

    if (bookPtr == NULL)
    {
        puts("\v\t\t\tError opening the book information file");
    }
    else
    {
        puts("\t\t\t_____________________________________________________________________________________________________________________________________________________");    
        puts("\v\t\t\tBook_id\t\tTitle\t\t\tAuthor\t\t\t\t    publisher\t\t\tedition\t   pub_year\tCopies\t  Rack_no.");
        puts("\t\t\t_____________________________________________________________________________________________________________________________________________________");
        

        while (!feof(bookPtr))
        {   
            BOOK book;
            int  result = fread(&book, sizeof(BOOK), 1, bookPtr);
            if(result != 0 && book.id != 0)
            {
                printf("\n\t\t\t%-10u %-29s%-39s%-29s%-10s%-4u\t%-10u%-10u\n", book.id, book.title, book.author, book.publisher, book.edition,book.pub_year, book.copies, book.rack);
                puts("\t\t\t`````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````");
            
            }
        }
        puts("\v\t\t\t_____________________________________________________________________________________________________________________________________________________");

        fclose(bookPtr);

    }
    puts("\v");
    int choice;
    printf("\v\v\v\v\v\v\v\t\t\t\t\tEnter 0 to go back to the main menu");
    printf("%s", "\t\t\t\t(Enter your choice here)->\t");

    scanf("%d", &choice);

    if (choice == 0)
    {
        // go to the customized view
    }
}

// a function that's used to issue books and update all the dependent records
void issueBook(void)
{
    system("clear"); // works on linux (comment this line while using windows)
    // system("cls")  // uncomment this line while on windows
    
    int TRU = 0, FOLS = 1; // variable to control entry into loops or functions
    int x = FOLS, y = FOLS;; // variable to control the flow of execution of command
    unsigned int student_id, book_id;

    bookPtr = fopen("books.dat","rb+"); // contains books' info
    studentPtr = fopen("student.dat", "rb+"); // contains students' info
    issuedBookPtr = fopen("issuedBook.dat", "a+"); // contains issued books' info
    
    puts("\v\t\t\t\t\t````````````````````````");
    puts("\t\t\t\t\t\t\033[22;34mISSUE BOOK\033[0m");
    puts("\t\t\t\t\t........................\v\v\v\v");

    // checks if the file is opened or not
    if (bookPtr == NULL || studentPtr == NULL || issuedBookPtr == NULL)
    {
        puts("\v\v\t\t\tError: The required files could not be oppened");
    }
    // executes when file is open
    else
    {
        // time 


        // // struct containing the time members
        // time_t t = time(NULL);
        // struct tm tm = *localtime(&t);

        // // the current and future time variables
        // int day = tm.tm_mday, 
        //     month = tm.tm_mon + 1, 
        //     year = tm.tm_year + 1900
        //     ;
        
        // // displaying current date of the system
        // printf("\nCurrent Date: %d/%d/%d", day, month, year);




        // checks if the book exists
        printf("%s","\v\v\t\tEnter student id\t\t\t\t->\t");
        scanf("%d", &student_id);
        int invalid_entry = 'n'; // to check for zero id
        if(student_id == 0)
        {
            invalid_entry = 'y';
        }


        // executes when the book exists
        while (!feof(studentPtr) && invalid_entry == 'n')
        {
            int result2 = fread(&student, sizeof(STUDENT), 1, studentPtr);
            if(result2 != 0 && student.id == student_id)
                {
                    puts("\v\v\t\t______________________________________\n");
                    puts("\t\tproceed, the student id exist");
                    puts("\t\t______________________________________\v\v");
                    y = TRU; // to enable the book to be checked
                }
            
        }

        // number of books borrowed (cant issue more than three books)
        int count = 0;
        char dont_issue = 'n';
        while(!feof(issuedBookPtr) && invalid_entry == 'n'){
            ISSUEDBOOK issuedbook;
            int result = fread(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);
            if (result != 0 && issuedbook.student_id == student_id) {
                count += result;
            }
            if (count >= 3) {
                dont_issue = 'y'; // has three books
            }
            
        }
        

        while (y == TRU && count < 3)
        {   
            y = FOLS; // to stop the loop
            printf("%s", "\v\v\t\tEnter id of the book to issue\t\t\t->\t");
            scanf("%u", &book_id);



            int count = 0; // to keep track of the record currently read
            char stop = 'n'; // to halt the loop when the record is found

            

            while (!feof(bookPtr) && stop == 'n')
            {

                BOOK book;
                int  result = fread(&book, sizeof(BOOK), 1, bookPtr); // checks if the record is empty
                count += result; // keeps track of the record number currently read

                if ( (result != 0) &&  book.id == book_id )
                    {
                    // set cursor at the begining of the record 
                    fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);
                    puts("\v\v\t\t____________________________________________________________________");

                    printf("\v\t\tOld record -> \t%-6d%-16s%-11s%u\n", book.id, book.title, 
                            book.author, book.copies);

                    // books with less than 1 copies cant be issued
                    if (book.copies > 0) 
                    {
                        
                        x = TRU; // this indicates that the book is available
                        stop = 'y';
                        // decrement copies by one                            
                        --book.copies;

                        // set cursor at the begining of the record 
                        fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);

                        // change the records
                        fwrite(&book, sizeof(BOOK), 1, bookPtr);
                        printf("\t\tNew record -> \t%-6d%-16s%-11s%u\n", book.id, book.title,book.author, book.copies); 
                        puts("\v\t\t____________________________________________________________________");
                        

                        puts("\v\v\v\v\t\tRecord is successfully updated ");
                    }
                    
                }

            }

            // message if the book is out of stock
            if(stop == 'n'){
                puts("\v\v\v\v\t\t\t\tOops! The book is out of stock!!!");
            }

            
        }
        if (dont_issue == 'y') {
            puts("\v\v\t\t____________________________________________________________________");
            printf("\t\t\tError: Can not issue more than three books!");
            puts("\n\t\t____________________________________________________________________");
        }
        if (invalid_entry == 'y') {
            puts("\v\v\t\t____________________________________________________________________");
            printf("\n\t\t\tError: Invalid id (id of 0 is not allowed)!\n");
            puts("\t\t____________________________________________________________________");
        }
        

        // executes when the student exists; writes to the issued books' record
        if(x == TRU && y == FOLS )
        {
            ISSUEDBOOK issuedbook;

            // struct containing the time members
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);

            // the current and future time variables
            issuedbook.date.b_day = tm.tm_mday, 
            issuedbook.date.b_month = tm.tm_mon + 1, 
            issuedbook.date.b_year = tm.tm_year + 1900
            ;
            
            // initialize return dates to zero (0)
            issuedbook.date.r_day = 0, 
            issuedbook.date.r_month = 0, 
            issuedbook.date.r_year = 0
            ;

            // a function to generate the return date
            boro_return_date(issuedbook.date.b_day, issuedbook.date.b_month, issuedbook.date.b_year,
                            &issuedbook.date.r_day, &issuedbook.date.r_month, &issuedbook.date.r_year);

            puts("\v\v\t\t\tstoring the data..\v");
            sleep(1);
            issuedbook.student_id = student_id;
            issuedbook.book_id = book_id;

            fwrite(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);

        }
        
        // fclose to close all the opened files to save changes 
        fclose(bookPtr);
        fclose(studentPtr);
        fclose(issuedBookPtr);
    
        puts("\v\v\v\v\v\v\v\v\v\v\t\t####################################################################");
        int choice;
        printf("%s", "\n\t\tEnter 1 to continue or 0 to exit: \n");
        printf("%s", "\v\t\t(Enter your choice here)->\t");
        scanf("%d", &choice);
        if (choice == 1)
        {
            issueBook();
        }

    

    }
}

// a list of the students' id against the book's id they borrowed
void viewIssuedBook(void)
{
    system("clear"); // works only on ubuntu
    
    puts("\v\t\t\t\t\t\t\t\t```````````````````````````````````");
    printf("%s","\t\t\t\t\t\t\t\t\t\033[22;34mLIST OF ISSUED BOOKS\033[0m\n");
    puts("\t\t\t\t\t\t\t\t```````````````````````````````````\v\v\v");

    issuedBookPtr = fopen("issuedBook.dat", "rb+");

    if (issuedBookPtr == NULL)
    {
        puts("\v\v\t\tError opening the issuedBook information file");
    }
    else
    {
    
        puts("\v\t\t\t\t\tStudent_id\tBook_id\t\tFrom\t\t  To");
        puts("\t\t\t\t\t________________________________________________________________________________\n");

        while (!feof(issuedBookPtr))
        {
            int  result = fread(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);
            if(result != 0 && issuedbook.student_id != 0)
            {

                printf("\t\t\t\t\t%10d%10d", issuedbook.student_id, issuedbook.book_id);
                printf("\t\t%2d/%2d/%4d",issuedbook.date.b_day,issuedbook.date.b_month,issuedbook.date.b_year);
                printf("\t%2d/%2d/%4d\n",issuedbook.date.r_day, issuedbook.date.r_month, issuedbook.date.r_year);
                puts("\t\t\t\t\t`````````````````````````````````````````````````````````````````````````````````\n");
            }
        }

        fclose(issuedBookPtr);

        puts("\v");
        int choice;

        printf("\v\v\v\v\v\v\v\t\t\t\t\t\t\t\t######################################\n");
        printf("\t\t\t\t\t\t\t\tEnter 1 to filter\n\t\t\t\t\t\t\t\tEnter 0 to go back to the main menu \n\t\t\t\t\t\t\t\t->\t");
        // printf("%s", "\t\t(Enter your choice here)->\t");

        scanf("%d", &choice);

        if (choice == 1)
        {
            searchissued();
        }
        else
        {
            // goes to the customized librabrian view
        }
        
    }
}

// a function to update the books' records except the id
void updateBook(void)
{
    system("clear");
    bookPtr = fopen("books.dat", "rb+");


    int count = 0; // to keep track of the record currently read
    char stop = 'n'; // to halt the loop when the record is found

    
    puts("\v\t\t\t\t\t\t\t``````````````````````````````````");
    puts("\t\t\t\t\t\t\t\t\033[22;34mUPDATE BOOK\033[0m");
    puts("\t\t\t\t\t\t\t``````````````````````````````````");

    // entry of id used for verification
    printf("%s", "\v\v\t\t\t\t\tEnter an id of the book to update\t\t\t->  ");
    unsigned int book_id;
    scanf("%u", &book_id);


    while (!feof(bookPtr) && stop == 'n')
    {

        BOOK book;
        int  result = fread(&book, sizeof(BOOK), 1, bookPtr); // checks if the record is empty
        count += result; // keeps track of the record number currently read

        if ( (result != 0) &&  book.id == book_id  )
            {
            // set cursor at the begining of the record 
            fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);

            puts("\v\v\t\t\t___________________________________________________________________________________________________________________________________________________________"); 
            printf("\n\t\t\t| Old record | -> %-10u %-29s%-39s%-29s%-10s%-4u\t%-10u%-10u\n", book.id, book.title, book.author, book.publisher, book.edition,book.pub_year, book.copies, book.rack);
            puts("\t\t\t___________________________________________________________________________________________________________________________________________________________");    

            printf("%s", "\n\v\t\t\tEnter title, author, publisher and edition. (e.g c-programming christopher Longhorn 4th )\t>\t");
            scanf("%29s%29s%29s%9s", book.title, book.author, book.publisher, book.edition);

            printf("%s", "\n\v\t\t\tEnter publication_year, copies and rack_number. (e.g 2013 20 122 )\t>\t");

            unsigned int copies, rack, pub_year;
            scanf("%u%u%u",&pub_year,&copies, &rack );
            book.rack = rack;
            book.copies = copies;
            book.pub_year = pub_year;

            // set cursor at the begining of the record 
            fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);
            fwrite(&book, sizeof(BOOK), 1, bookPtr);
            puts("\v\v\v\v\t\t\t\t\tRecord is successfully updated ");


            puts("\v\v\t\t\t___________________________________________________________________________________________________________________________________________________________"); 
            printf("\n\t\t\t| New record | -> %-10u %-29s%-39s%-29s%-10s%-4u\t%-10u%-10u\n", book.id, book.title, book.author, book.publisher, book.edition,book.pub_year, book.copies, book.rack);
            puts("\t\t\t___________________________________________________________________________________________________________________________________________________________");    

            stop = 'y'; // terminate the loop
            // sleep(3);
            }

    }

    // variable stop does not change if the book does not exist
    while(stop == 'n'){
        puts("\v\v\t\t\t\t\t_________________________________________________________________\n");

        puts("\t\t\t\t\t\tError: The book id does not exist");
        puts("\t\t\t\t\t_________________________________________________________________\v");
        stop = 'y'; // terminate the loop
    }
    
    rewind(bookPtr); // returns the cursor to the begining of the file 
    fclose(bookPtr);

    puts("\v");
    int choice;
    printf("\v\v\v\v\v\v\v\t\t\t\t\tEnter 0 to go back to the main menu or 1 to continue\t->\t");
    scanf("%d", &choice);

    if (choice == 0)
    {
        // this goes to the customized view of the librabrian
    }
    else
    {
        updateBook();
    }
    

}

// a function to delete a book
void deleteBook(void)
{
    system("clear"); // on windows system("cls");
    bookPtr = fopen("books.dat", "rb+"); // contains the books' info
    issuedBookPtr = fopen("issuedBook.dat", "rb+"); // contains the issued books' info


    int count = 0; // to keep track of the record currently read
    char stop = 'n'; // to halt the loop when the record is found
    
    puts("\v\t\t\t\t\t\t\t\t````````````````````````````````");
    puts("\t\t\t\t\t\t\t\t\t\033[22;34mDELETE BOOK\033[0m");
    puts("\t\t\t\t\t\t\t\t````````````````````````````````\v\v");

    // entry of id used for verification
    printf("%s", "\v\v\t\t\t\t\tEnter an id of the book to delete \t\t\t->\t");
    unsigned int book_id;
    scanf("%u", &book_id);

    // to check for the existence of the book id
    while (!feof(bookPtr) && stop == 'n')
    {

        BOOK book;
        int  del = 0, result = fread(&book, sizeof(BOOK), 1, bookPtr); // checks if the record is empty
        count += result; // keeps track of the record number currently read

        if ( (result != 0) &&  book.id == book_id  )
        {
            stop = 'y'; // the id exists

            // to ensure borrowed book is not deleted by checking if its borrowed
            while(!feof(issuedBookPtr) && del == 0)
            {
                ISSUEDBOOK issuedbook;

                int result = fread(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);
                    if (result != 0 && book_id == issuedbook.book_id) {
                        puts("\v\v\v\v\t\t\t\t\t________________________________________________________________________________________");
                        puts("\n\t\t\t\t\t\tError: Record of borrowed books can not be deleted until returned");
                        puts("\t\t\t\t\t________________________________________________________________________________________");
                        del = 1; // initializes the del to false (cant be deleted)
                    }
            }
            
            // if not borrowed then delete
            if(del == 0 )
            {
                
                // set cursor at the begining of the record 
                fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);

                puts("\v\v\v\v\t\t\t________________________________________________________________________________________________________________________________________________________________"); 
                printf("\t\t\tRecord to be deleted -> (id)%-10u%-29s%-39s%-29s%-10s%-4u %-10u%-10u\n", book.id, book.title, book.author, book.publisher, book.edition,book.pub_year, book.copies, book.rack);
                puts("\t\t\t________________________________________________________________________________________________________________________________________________________________"); 
            
                int confirm;
                printf("\v\v\v\t\t\t\t\tConfirm deletion by entering 1 otherwise 0 (then press enter key)\t\t ->\t");
                scanf("%d", &confirm);
                if (confirm == 1) 
                {
                    // seta blank record to overwrite the record  
                    BOOK blankbook = {0, 0, 0, 0,"", "","",""};

                    // set cursor at the begining of the record 
                    fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);
                    fwrite(&blankbook, sizeof(BOOK), 1, bookPtr);
                    puts("\v\v\v\v\t\t\t\t\t________________________________________________________________________________________");
                    puts("\n\t\t\t\t\t\t\t\tHurray: Record is successfully deleted ");
                    puts("\t\t\t\t\t________________________________________________________________________________________");
                }
                else
                {
                    puts("\v\v\v\v\t\t\t________________________________________________________________________________________________________________________________________________________________"); 
                    printf("\t\t\tRetained record -> (id)%-10u%-29s%-39s%-29s%-10s%-4u %-10u%-10u\n", book.id, book.title, book.author, book.publisher, book.edition,book.pub_year, book.copies, book.rack);
                    puts("\t\t\t________________________________________________________________________________________________________________________________________________________________"); 
            
                }
                

            }
        }

    }

    // variable stop does not change if the book does not exist
    if(stop == 'n')
    {
        puts("\v\v\v\v\t\t\t\t\t________________________________________________________________\n");
        puts("\t\t\t\t\t\t\tError: The book id does not exist!");
        puts("\t\t\t\t\t________________________________________________________________");
    }
    
    rewind(bookPtr); // returns the cursor to the begining of the file 
    fclose(bookPtr);
    
    puts("\v");
    int choice;
    printf("\v\v\v\v\v\v\v\t\t\t\t\tEnter 0 to go back to the main menu or 1 to continue\t->\t");
    scanf("%d", &choice);

    if (choice == 0)
    {
        // this goes to the customized view of the librabrian by exiting this program
    }
    else
    {
        deleteBook();
    }
}

// a function used to return a book and update all the dependent records
void returnBook(void)
{
    system("clear");

    puts("\v\t\t\t\t\t\t\t\t````````````````````````````````");
    puts("\t\t\t\t\t\t\t\t\t   \033[22;34mRETURN BOOK\033[0m\n");
    puts("\t\t\t\t\t\t\t\t````````````````````````````````\v\v");
    
    issuedBookPtr = fopen("issuedBook.dat", "rb+");
    bookPtr = fopen("books.dat","rb+");

    if (bookPtr == NULL || issuedBookPtr == NULL ) 
    {
        puts("Error: The required files could not be opened");
    }
    else
    {
        char tru = 'y', fols = 'y';
        unsigned int student_id, book_id;
        printf("%s", "\v\v\t\t\tEnter student id \t");
        scanf("%u", &student_id);
        
        printf("%s", "\v\v\t\t\tEnter book id \t");
        scanf("%u", &book_id);


        // delete record from issuedbook list
        int count = 0; // keep track of the record number scanned
        while(!feof(issuedBookPtr) && tru == 'y')
        {

            ISSUEDBOOK issuedbook;
            // to check if the record is read (returns 1 when read otherwise 0)
            int result = fread(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);
            count += result;

            if (result != 0 && book_id == issuedbook.book_id && student_id == issuedbook.student_id ) 
            {   
                tru = 'n'; // to ensure that only one record is modified each time a return occurs
                fseek(issuedBookPtr, (count - 1)*sizeof(ISSUEDBOOK), SEEK_SET );
                ISSUEDBOOK blankbook = { 0,0,{0,0,0,0,0,0}};
                fseek(issuedBookPtr, (count - 1)*sizeof(ISSUEDBOOK), SEEK_SET );
                fwrite(&blankbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);
            }
        }

        // return the cursor to the beginning of the first record
        rewind(issuedBookPtr);
        fclose(issuedBookPtr);

        // update the book.copies (increment)
        count = 0;
        while(!feof(bookPtr))
        {
            BOOK book;
            int result1 = fread(&book, sizeof(BOOK), 1, bookPtr);
            count += result1;

            if (result1 != 0 && book_id == book.id) 
            {
                fols = 'n';
                // mov cursor to the record
                fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);
                // increment the returned book's record by incrementing it by 1
                ++book.copies;
                // mov cursor to the record
                fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);
                fwrite(&book, sizeof(BOOK), 1, bookPtr);
            }
            
        }
        rewind(bookPtr);
        fclose(bookPtr);

        if (tru == 'n' && fols == 'n') {
            puts("\v\v\v\v\t\t\t________________________________________________________________________________________\n");
            puts("\t\t\t\tThe records are successfully updated");
            puts("\t\t\t________________________________________________________________________________________");

        }
        else if (tru == 'n' && fols == 'y')
        {
            puts("\v\v\v\v\t\t\t________________________________________________________________________________________\n");
            puts("\t\t\t\tError: The book id does not exist");
            puts("\t\t\t________________________________________________________________________________________");
        }
        else if (tru == 'y' && fols == 'n' )
        {
            puts("\v\v\v\v\t\t\t________________________________________________________________________________________\n");
            puts("\t\t\t\tError: The records does not exist in the issued books");
            puts("\t\t\t________________________________________________________________________________________");
        }
        else
        {
            puts("\v\v\v\v\t\t\t________________________________________________________________________________________\n");
            puts("\t\t\t\tOops! The system has no records on this book and its lease");
            puts("\t\t\t________________________________________________________________________________________");
        }

        sleep(3);
        
    }
}

/* a function that uses a subset of a characters within the book title or
 author to suggestions of possible available books to search or borrow*/
void suggestBook(void)
{
    system("clear");

    puts("\v\t\t\t\t\t\t\t\t\t\t```````````````````````````");
    puts("\t\t\t\t\t\t\t\t\t\t\t\033[22;34mSUGGEST BOOK\033[0m");
    puts("\t\t\t\t\t\t\t\t\t\t...........................\v\v\v\v");

    bookPtr = fopen("books.dat", "rb+");
    if (bookPtr == NULL)
        printf("Error: Could not open the books file");
    else
    {
        int choice;
        
        printf("%s", "\v\t\t\t\t\t\t________________________________________________________________________________________\n\n"
                "\t\t\t\t\t\t\t|1| Suggest by Author\t\t<-- or -->\t\t|2| Suggest by Title\n"
                "\t\t\t\t\t\t________________________________________________________________________________________\n"
                );
        printf("%s", "\v\v\t\t\t\t\t\t(Enter your choice here)\t\t\t\t\t->\t");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\v\v\t\t\t\t\t\tEnter the Author (even part of the name works!)\t\t\t->\t");
                char author[40], books_found = 'n';
                scanf("%39s", author);
                

                puts("\v\v"); //just to do add vertical tab
                puts("\t\t\t_____________________________________________________________________________________________________________________________________________________");    
                puts("\v\t\t\tBook_id\t\tTitle\t\t\tAuthor\t\t\t\t    publisher\t\t\tedition\t   pub_year\tCopies\t  Rack_no.");
                puts("\t\t\t_____________________________________________________________________________________________________________________________________________________");
        
                // lists the info of books that has been written by the entered author
                while (!feof(bookPtr))
                    {   
                        BOOK book;
                        int  result = fread(&book, sizeof(BOOK), 1, bookPtr);
                        if(result != 0 && book.id != 0 && strstr(book.author, author) != NULL)
                        {
                            printf("\n\t\t\t%-10u %-29s%-39s%-29s%-10s%-4u\t%-10u%-10u\n", book.id, book.title, book.author, book.publisher, book.edition,book.pub_year, book.copies, book.rack);
                            puts("\t\t\t`````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````");
                            books_found = 'y'; 
                        }
                    }
                    puts("\v\t\t\t_____________________________________________________________________________________________________________________________________________________");
                    
                    if (books_found == 'n')
                            puts("\n\t\t\t\tOops! Could not get a suggestion from our databases");
                    
                    fclose(bookPtr);
                    break;
                
            case 2:
                printf("\v\v\t\t\t\t\t\tEnter the Title (even part of the title works!)\t\t\t->\t");
                char title[40], books_found2 = 'n' ;
                scanf("%39s", title);

                puts("\v\v"); //just to do add vertical tab
                puts("\t\t\t_____________________________________________________________________________________________________________________________________________________");    
                puts("\v\t\t\tBook_id\t\tTitle\t\t\tAuthor\t\t\t\t    publisher\t\t\tedition\t   pub_year\tCopies\t  Rack_no.");
                puts("\t\t\t_____________________________________________________________________________________________________________________________________________________");
        
                // lists the info of books that contains the entered title
                while (!feof(bookPtr))
                    {   
                        BOOK book;
                        int  result = fread(&book, sizeof(BOOK), 1, bookPtr);
                        if(result != 0 && book.id != 0 && strstr(book.title, title) != NULL)
                        {
                              printf("\n\t\t\t%-10u %-29s%-39s%-29s%-10s%-4u\t%-10u%-10u\n", book.id, book.title, book.author, book.publisher, book.edition,book.pub_year, book.copies, book.rack);
                            puts("\t\t\t`````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````");
                            books_found2 = 'y';
                        }
                    }
                puts("\v\t\t\t_____________________________________________________________________________________________________________________________________________________");

                if (books_found2 == 'n')
                    puts("\n\t\t\t\t\t\tOops! Could not get a suggestion from our databases");

                break;
                
                

            default:
                // user();
                break;
        }

    }
}

// filters the issued book either by student id or by book id
void searchissued(void)
{
    system("clear");

    puts("\v\t\t\t\t\t\t\t\t```````````````````````````````````");
    printf("%s","\t\t\t\t\t\t\t\t\t\033[22;34mFILTER ISSUED BOOK\033[0m\n");
    puts("\t\t\t\t\t\t\t\t```````````````````````````````````\v\v\v");
    issuedBookPtr = fopen("issuedBook.dat", "rb+");

    if (issuedBookPtr == NULL) {
        printf("\v\v\t\t\tError: Could not open the required files");
    }
    else
    {
        int choice;
        puts("\v\t\t\t1. Filter by student id\n"
            "\t\t\t2. Filter by Book id\n");
        printf("\v\t\t\t->\t");
        scanf("%d", &choice);

        unsigned int student_id;
        unsigned int book_id;
        
        switch (choice)
        {
            case 1:
                printf("\v\v\t\t\tEnter the user id to search\t\t->\t");
                scanf("%u", &student_id);

                puts("\v\v\t\t\t\t\tStudent_id\tBook_id\t\tFrom\t\t  To");
                puts("\t\t\t\t\t________________________________________________________________________________\n");
                while(!feof(issuedBookPtr))
                {
                    ISSUEDBOOK issuedbook;
                    fread(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);
                    if (student_id == issuedbook.student_id) 
                    {
                        printf("\t\t\t\t\t%10d%10d", issuedbook.student_id, issuedbook.book_id);
                        printf("\t\t%2d/%2d/%4d",issuedbook.date.b_day,issuedbook.date.b_month,issuedbook.date.b_year);
                        printf("\t%2d/%2d/%4d\n",issuedbook.date.r_day, issuedbook.date.r_month, issuedbook.date.r_year);
                        puts("\t\t\t\t\t`````````````````````````````````````````````````````````````````````````````````\n");
                    }
                }
                fclose(issuedBookPtr);
                break;
            case 2:
                printf("\v\v\t\t\tEnter the book id to search\t\t->\t");
                scanf("%u", &book_id);

                puts("\v\v\t\t\t\t\tStudent_id\tBook_id\t\tFrom\t\t  To");
                puts("\t\t\t\t\t________________________________________________________________________________\n");
                while(!feof(issuedBookPtr))
                {
                    ISSUEDBOOK issuedbook;
                    fread(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);
                    if (book_id == issuedbook.book_id) {
                        printf("\t\t\t\t\t%10d%10d", issuedbook.student_id, issuedbook.book_id);
                        printf("\t\t%2d/%2d/%4d",issuedbook.date.b_day,issuedbook.date.b_month,issuedbook.date.b_year);
                        printf("\t%2d/%2d/%4d\n",issuedbook.date.r_day, issuedbook.date.r_month, issuedbook.date.r_year);
                        puts("\t\t\t\t\t`````````````````````````````````````````````````````````````````````````````````\n");
                    }
                }
                fclose(issuedBookPtr);
                break;

            default:
                break;
        }        
        puts("\v");
        int choice2;

        printf("\v\v\v\v\v\v\v\t\t\t\t\t\t\t\t######################################\n");
        printf("\t\t\t\t\t\t\t\tEnter 0 to go back to the main menu ->\t");
        // printf("%s", "\t\t(Enter your choice here)->\t");

        scanf("%d", &choice2);

        if (choice2 == 0)
        {
            // goes to the customized librabrian view
        }
    }

}