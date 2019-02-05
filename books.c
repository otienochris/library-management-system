// #include "structs.c"
#include <stdio.h>
#include <time.h>

typedef struct
{
    unsigned int student_id, book_id;
    char fname[30], title[30];    
} ISSUEDBOOK;
typedef struct
{
    unsigned int id, copies;
    char title[30], author[30];
} BOOK;
typedef struct
{
    // COURSE course;
    // DATE dob;
    unsigned int day, id, month, year ;
    char  fname[30], lname[30];
    char faculty[30], department[30], course_title[30];
} STUDENT;

void menu(void);

//  global pointer
FILE *bookPtr, *studentPtr, *userPtr, *issuedBookPtr;

// global struct declaration
// BOOK book;
STUDENT student;
ISSUEDBOOK issuedbook;

// a function that adds a book(s) to books.dat file    
void addBook(void)
{
    system("clear");
    unsigned int book_id;
    BOOK book;

    bookPtr = fopen("books.dat", "a+");

    puts("\v\v\t\t\t\t\t\tAdd Book:");
    printf("%s", "\n\t\tEnter 0 as book id to exit: \n");


    printf("%s", "\v\t\tEnter book id: ");
    scanf("%u", &book_id);
        
            
        while (!feof(bookPtr))
        {
            fread(&book, sizeof(BOOK), 1, bookPtr);
            if (book_id == book.id)
            {
                puts("\v\t\tError: The book id exists");
                sleep(2);
                book_id = 0 ;
            }
        }


    

        while (book_id != 0){
            book.id = book_id;

            puts("\t\tmultiple names must be separated using a hyphen(eg c-programming otieno-chris 900)");
            printf("%s", "\n\v\t\ttitle, author and copies\n\t\t>");


            // fscanf(stdin, "%14s%9s%d", book.title, book.author, &book.copies);
            scanf("%29s%29s%d", book.title, book.author, &book.copies);

         
            fwrite(&book, sizeof(BOOK), 1, bookPtr);

            int choice;
            printf("%s", "\n\t\tEnter 1 to continue or 0 to exit: \n");
            printf("%s", "\v\t\t(Enter your choice here)->\t");
            scanf("%d", &choice);

            
            if (choice == 1)
            {
                addBook();
            }
            else
            {
       
                printf("%s", "\v\t\tloading...\n");
                sleep(1);
                printf("%s", "\v\t\trestart the program to view changes in the files...\n");
                sleep(2);
                menu();
            }
                


        }


        menu ();
    

}

// search for a book
void searchBook(void)
{
    system("clear");


    puts("\t\tSEARCH BOOK:");
    bookPtr = fopen("books.dat", "rb");

    if (bookPtr == NULL)
    {
        puts("Error opening the book information file");
    }
    else
    {
        unsigned int search_id;
        char search_title[30];
        int choice;

        printf("%s", "\v\t\t***********************\n"
                "\t\t1 -> Search by title:\n "
                "\t\t***********************\n"
                "\t\t2 -> search by id:\n"
                "\t\t***********************\n"
                );
        printf("%s", "\v\t\t(Enter your choice here)->\t");

        scanf("%d", &choice);

        switch(choice){
            case 1:

                puts("\n\t\tEnter the title of the book to search:");
                printf("%s", "\v\t\t(Enter the title here)->\t");
                scanf("%29s", search_title);

                puts("\v\t\tBook_id\t\t\t\tTitle\t\t\t\tAuthor\t\t\t\tCopies");            
                while (!feof(stdin))
                {
                    
                while (!feof(bookPtr))
                {
                    BOOK book;
                    int  result = fread(&book, sizeof(BOOK), 1, bookPtr);
                    
                    if ((strcmp(book.title, search_title)==0) && (result != 0) )
                        {
                        printf("\v\t\t%d\t\t\t\t%s\t\t\t\t%s\t\t\t\t%d\n", book.id, book.title, book.author, book.copies);
                        }

                }
                
                // puts("\n\t\tSearch for another book: ");
                puts("\n\n\n\n\v\v\v\v\v\v\v\v\t\tTo Exit to main menu press: \n\t\tctrl+D (linux) or ctrl+Z(windows)");
                printf("%s", "\v\t\t(Entery goes here)->\t");
                scanf("%29s", search_title);
                }
                break;

            case 2:
                puts("\n\t\tEnter the id of the book to search:");
                printf("%s", "\v\t\t(Enter the id here)->\t");                
                scanf("%u", &search_id);

                puts("\v\t\tBook_id\t\t\t\tTitle\t\t\t\tAuthor\t\t\t\tCopies");            
                while (!feof(stdin))
                {
                    
                while (!feof(bookPtr))
                {
                    BOOK book;
                    int  result = fread(&book, sizeof(BOOK), 1, bookPtr);
                    if ( (result != 0) &&  book.id == search_id  )
                        {
                        printf("\v\t\t%d\t\t\t\t%s\t\t\t\t%s\t\t\t\t%d\n", book.id, book.title, book.author, book.copies);
                        }

                }
                
                // puts("\n\t\tSearch for another book: ");
                puts("\n\n\n\n\n\n\v\v\v\v\v\v\v\t\tTo Exit to main menu press: \n\t\tctrl+D (linux) or ctrl+Z(windows)");
                printf("%s", "\v\t\t(Enter goes here)->\t");                
                scanf("%u", &search_id);
                }

        }


        fclose(bookPtr);
        menu();
        }
}

// a function that returns all the books' inventory
void viewBooks(void)
{
    system("clear"); // works only on ubuntu
    // system("COLOR FC");

    puts("\v\t\t\t\t\t\t\t\t\tLIST OF BOOKS:");
    bookPtr = fopen("books.dat", "rb");

    if (bookPtr == NULL)
    {
        puts("Error opening the book information file");
    }
    else
    {
    
        puts("\v\t\t\tBook_id\t\t\tTitle\t\t\tAuthor\t\t\tCopies");
        while (!feof(bookPtr))
        {   
            BOOK book;
            int  result = fread(&book, sizeof(BOOK), 1, bookPtr);
            if(result != 0 && book.id != 0)
            {
                printf("\n\t\t\t%d\t\t\t%s\t\t\t%s\t\t\t%d\n", book.id, book.title, book.author, book.copies);
            }
        }

        fclose(bookPtr);

    }
    puts("\v");
    int choice;
    printf("\v\v\v\v\v\v\v\t\t\tEnter 0 to go back to the main menu");
    printf("%s", "\t\t(Enter your choice here)->\t");

    scanf("%d", &choice);

    if (choice == 0)
    {
        menu();
    }
}

void issueBook(void)
{
    system("clear");
    int TRU = 0, FOLS = 1;
    int x = FOLS, y = FOLS; //stop = FOLS; // variable to control the flow of execution of command
    unsigned int student_id, book_id;
    // char title[30], fname[30];

    bookPtr = fopen("books.dat","rb+");
    studentPtr = fopen("student.dat", "rb+");
    issuedBookPtr = fopen("issuedBook.dat", "a+");
    puts("\v\t\tISSUE BOOK:\v\v\v\v");

    // checks if the file is opened or not
    if (bookPtr == NULL || studentPtr == NULL || issuedBookPtr == NULL)
    {
        puts("\v\v\t\t\tError: The required files could not be oppened");
    }
    // executes when file is open
    else
    {
        // checks if the book exists
                // x = FOLS;
        printf("%s","\t\tEnter student id\n\t\t>\t");
        scanf("%d", &student_id);
        


        // executes when the book exists
        while (!feof(studentPtr))
        {
            int result2 = fread(&student, sizeof(STUDENT), 1, studentPtr);
            if(result2 != 0 && student.id == student_id)
                {
                    // char fname[30] = student.fname;
                    puts("\v\v\t\tproceed, the student id exist\v\v");
                    y = TRU; // to enable the book to be checked
                }
            
        }

        while (y == TRU)
        {   
            y = FOLS; // to stop the loop
            printf("%s", "\v\v\t\tEnter id of the book to issue");
            printf("%s", "\n\t\t(Enter the id here)->\t");                
            scanf("%u", &book_id);



            int count = 0; // to keep track of the record currently read
            // char stop = 'n'; // to halt the loop when the record is found

            

            while (!feof(bookPtr))
            {

                BOOK book;
                int  result = fread(&book, sizeof(BOOK), 1, bookPtr); // checks if the record is empty
                count += result; // keeps track of the record number currently read

                if ( (result != 0) &&  book.id == book_id )
                    {
                    // set cursor at the begining of the record 
                    fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);
                    printf("\v\v\t\t\tOld record -> \t%-6d%-16s%-11s%u\n\n", book.id, book.title, 
                            book.author, book.copies);

                    if (book.copies > 0) {
                        
                        x = TRU; // this indicates that the book is available
                        // stop = 'y';
                        // decrement copies by one                            
                        --book.copies;

                        // set cursor at the begining of the record 
                        fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);

                        // change the records
                        fwrite(&book, sizeof(BOOK), 1, bookPtr);
                        printf("\v\v\t\t\tNew record -> \t%-6d%-16s%-11s%u\n\n", book.id, book.title, 
                            book.author, book.copies);

                        puts("\v\v\v\v\t\tRecord is successfully update ");
                    }
                    // stop = 'y'; // terminate the loop
                    sleep(2);
                }

            }

        }

        // executes when the student exists
        while (x == TRU && y == FOLS )
        {
            puts("\v\v\t\t\tstoring the data..\v");
            sleep(1);
            issuedbook.student_id = student_id;
            // issuedbook.fname = student.fname;
            issuedbook.book_id = book_id;
            // issuedbook.title = book.title; 
            fwrite(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);

            x = FOLS; // just to demonstrate that x changed
            
        }
    /* 
            while(x==FOLS){
                puts("\v\v\v\v\t\t\t\tOops! The book is out of stock");
                x = TRU; // terminate this loop
            } */
        

            


        int choice;
        printf("%s", "\v\v\v\v\v\v\v\v\v\v\n\t\tEnter 1 to continue or 0 to exit: \n");
        printf("%s", "\v\t\t(Enter your choice here)->\t");
        scanf("%d", &choice);
        if (choice == 1)
        {
            issueBook();
        }

        fclose(bookPtr);
        fclose(studentPtr);
        fclose(issuedBookPtr);
    
        menu();

    }
}

void viewIssuedBook(void)
{
    system("clear"); // works only on ubuntu

    puts("\v\t\t\t\t\t\t\t\t\tLIST OF ISSUD BOOKS:");
    issuedBookPtr = fopen("issuedBook.dat", "rb");

    if (issuedBookPtr == NULL)
    {
        puts("Error opening the issuedBook information file");
    }
    else
    {
    
        puts("\v\t\t\tStudent_id\t\tBook_id");
        while (!feof(issuedBookPtr))
        {
            int  result = fread(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);
            if(result != 0 && issuedbook.student_id != 0)
            {
                printf("\n\t\t\t%d\t\t\t%d\n", issuedbook.student_id, issuedbook.book_id);
            }
        }

        fclose(bookPtr);

        puts("\v");
        int choice;
        printf("\v\v\v\v\v\v\v\t\t\tEnter 0 to go back to the main menu");
        printf("%s", "\t\t(Enter your choice here)->\t");

        scanf("%d", &choice);

        if (choice == 0)
        {
            menu();
        }
    }
}

void updateBook(void)
{
    bookPtr = fopen("books.dat", "rb+");


    int count = 0; // to keep track of the record currently read
    char stop = 'n'; // to halt the loop when the record is found

    // entry of id used for verification
    printf("%s", "\v\v\t\tEnter an id of the book to update ->");
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
            printf("\v\v\t\t\tOld record -> \t%-6d%-16s%-11s%u\n\n", book.id, book.title, 
                    book.author, book.copies);
            printf("%s", "\v\v\t\tEnter the new title, author and copies");
            scanf("%29s%29s",book.title, book.author);

            unsigned int copies;
            scanf("%u", &copies);
            book.copies = copies;

            // set cursor at the begining of the record 
            fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);
            fwrite(&book, sizeof(BOOK), 1, bookPtr);
            puts("\v\v\v\v\t\tRecord is successfully update ");
            printf("\v\t\t\tNew record -> %-6d%-16s%-11s%u\n", book.id, book.title, book.author, book.copies);

            stop = 'y'; // terminate the loop
            sleep(2);
            }

    }

    // variable stop does not change if the book does not exist
    while(stop == 'n'){
        puts("\v\v\t\t\tError: The book id does not exist");
        stop = 'y'; // terminate the loop
        sleep(2);
    }
    
    rewind(bookPtr); // returns the cursor to the begining of the file 
    fclose(bookPtr);
    menu();

}


void deleteBook(void)
{
    bookPtr = fopen("books.dat", "rb+");


    int count = 0; // to keep track of the record currently read
    char stop = 'n'; // to halt the loop when the record is found

    // entry of id used for verification
    printf("%s", "\v\v\t\tEnter an id of the book to update ->");
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
            printf("\v\v\t\t\tOld record -> \t%-6d%-16s%-11s%u\n\n", book.id, book.title, 
                    book.author, book.copies);
           
            BOOK blankbook = {0, 0 ,"", ""};


            // set cursor at the begining of the record 
            fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);
            fwrite(&blankbook, sizeof(BOOK), 1, bookPtr);
            puts("\v\v\v\v\t\tRecord is successfully deleted ");
            puts("press enter to continue");
            getchar();

            stop = 'y'; // terminate the loop
            sleep(2);
            }

    }

    // variable stop does not change if the book does not exist
    while(stop == 'n'){
        puts("\v\v\t\t\tError: The book id does not exist");
        stop = 'y'; // terminate the loop
        sleep(2);
    }
    
    rewind(bookPtr); // returns the cursor to the begining of the file 
    fclose(bookPtr);
    menu();
}

void returnBook(void)
{
    system("clear");

    puts("\v\t\tRETURN BOOK:\v\v\v\v");
    
    issuedBookPtr = fopen("issuedBook.dat", "rb+");
    bookPtr = fopen("books.dat","rb+");

    if (bookPtr == NULL || issuedBookPtr == NULL ) 
    {
        puts("Error: The required files could not be opened");
    }
    else
    {
        unsigned int book_id;
        printf("%s", "Enter book id");
        scanf("%u", &book_id);

        unsigned int student_id;
        printf("%s", "Enter student id");
        scanf("%u", &student_id);

        int count = 0;
        
        while(!feof(issuedBookPtr))
        {

            ISSUEDBOOK issuedbook;
            int result = fread(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);
            count += result;

            if (result != 0 && book_id == issuedbook.book_id && student_id == issuedbook.student_id ) 
            {
                fseek(issuedBookPtr, (count - 1)*sizeof(ISSUEDBOOK), SEEK_SET );
                ISSUEDBOOK blankbook = { 0, 0, "", "" };
                fseek(issuedBookPtr, (count - 1)*sizeof(ISSUEDBOOK), SEEK_SET );
                fwrite(&blankbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);
                puts("was here 1");
            }
        }
        rewind(issuedBookPtr);
        fclose(issuedBookPtr);


        count = 0;
        while(!feof(bookPtr))
        {
            BOOK book;
            int result1 = fread(&book, sizeof(BOOK), 1, bookPtr);
            count += result1;

            if (result1 != 0 && book_id == book.id) 
            {
                fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);
                ++book.copies;
                fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);
                fwrite(&book, sizeof(BOOK), 1, bookPtr);
                puts("was here 2");
            }
            
        }
        rewind(bookPtr);
        fclose(bookPtr);
        puts("The records are successfully updated");
        
        sleep(2);
        menu();
    }
}