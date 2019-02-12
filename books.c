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


    printf("%s", "\v\v\t\tEnter book id: ");
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


    

        if( book_id != 0 )
        {
            book.id = book_id;

            puts("\v\t\tNB:\tMultiple names must be separated using a hyphen(eg c-programming otieno-chris 900)");
            puts("\t\t---------------------------------------------------------------------------------------------------");
            printf("%s", "\n\v\t\tEnter title, author and copies (e.g c-programming christopher 100 )\t>\t");


            // fscanf(stdin, "%14s%9s%d", book.title, book.author, &book.copies);
            scanf("%29s%29s%d", book.title, book.author, &book.copies);

         
            fwrite(&book, sizeof(BOOK), 1, bookPtr);
        }
                
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
            printf("%s", "\v\v\t\tNB:\tPlease restart the program to view changes in the files...\n");
            puts("\t\t---------------------------------------------------------------------------------------");
            sleep(3);
            // menu();    
        }



}

// search for a book
void searchBook(void)
{
    system("clear");


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
        char search_title[30];
        int choice;

        printf("%s", "\v\t\t\t\t\t\t________________________________________________________________________________________\n\n"
                "\t\t\t\t\t\t\t|1| Search by title\t\t<-- or -->\t\t|2| Search by id\n"
                "\t\t\t\t\t\t________________________________________________________________________________________\n"
                );
        printf("%s", "\v\v\t\t\t\t\t\t(Enter your choice here)\t\t\t\t->\t");

        scanf("%d", &choice);

        switch(choice){
            case 1:

                printf("%s","\v\v\n\t\t\t\t\t\tEnter the title of the book to search:\t\t\t->\t");
                // printf("%s", "\v\t\t(Enter the title here)->\t");
                scanf("%29s", search_title);

                printf("%s","\v\v\t\t\t\t\t\tid\tTitle\t\t\t\tAuthor\t\t\t\tCopies\n");            
                puts("\t\t\t\t\t\t________________________________________________________________________________________\v");

                while (!feof(bookPtr))
                {
                    BOOK book;
                    int  result = fread(&book, sizeof(BOOK), 1, bookPtr);
                    
                    if ((strcmp(book.title, search_title)==0) && (result != 0) )
                        {
                        printf("\t\t\t\t\t\t%d\t%s\t\t\t\t%s\t\t\t\t%d\n", book.id, book.title, book.author, book.copies);
                        puts("\v\t\t\t\t\t\t````````````````````````````````````````````````````````````````````````````````````````");
                        }

                }
                puts("\v");
                int choice;
                puts("\v\v\v\v\v\v\v\t\t\t\t\t\t##########################################################################################");
                printf("\t\t\t\t\t\tEnter 0 to go back to the main menu");
                printf("%s", "\t\t(Enter your choice here)->\t");

                scanf("%d", &choice);

                if (choice == 0)
                {
                    // go to the customized view
                }
                
                
                break;

            case 2:
                
                printf("%s","\v\v\n\t\t\t\t\t\tEnter the id of the book to search:\t\t\t->\t");
                // printf("%s", "\v\t\t(Enter the title here)->\t");
                scanf("%d", &search_id);

                printf("%s","\v\v\t\t\t\t\t\tid\tTitle\t\t\t\tAuthor\t\t\t\tCopies\n");            
                puts("\t\t\t\t\t\t________________________________________________________________________________________\v");
                    
                while (!feof(bookPtr))
                {
                    BOOK book;
                    int  result = fread(&book, sizeof(BOOK), 1, bookPtr);
                    if ( (result != 0) &&  book.id == search_id  )
                        {
                        printf("\t\t\t\t\t\t%d\t%s\t\t\t\t%s\t\t\t\t%d\n", book.id, book.title, book.author, book.copies);
                        
                        puts("\v\t\t\t\t\t\t````````````````````````````````````````````````````````````````````````````````````````");
                        }

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


        fclose(bookPtr);
        // go to the customized view

        }
}

// a function that returns all the books' inventory
void viewBooks(void)
{
    system("clear"); // works only on ubuntu
    // system("COLOR FC");
    
    puts("\v\t\t\t\t\t\t\t\t\t\t\t\033[22;34mLIST OF BOOKS\033[0m");
    puts("\t\t\t\t\t\t\t\t\t\t`````````````````````````````");
    
    bookPtr = fopen("books.dat", "rb");

    if (bookPtr == NULL)
    {
        puts("\v\t\t\tError opening the book information file");
    }
    else
    {
        puts("\t\t\t\t________________________________________________________________________________________________________________________");    
        puts("\v\t\t\t\t\tBook_id\t\t\tTitle\t\t\tAuthor\t\t\tCopies");
        puts("\t\t\t\t________________________________________________________________________________________________________________________");
        

        while (!feof(bookPtr))
        {   
            BOOK book;
            int  result = fread(&book, sizeof(BOOK), 1, bookPtr);
            if(result != 0 && book.id != 0)
            {
                printf("\n\t\t\t\t\t%d\t\t\t%s\t\t\t%s\t\t\t%d\n", book.id, book.title, book.author, book.copies);
                puts("\t\t\t\t````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````");
            }
        }
        puts("\v\t\t\t\t________________________________________________________________________________________________________________________");

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
        // checks if the book exists
                // x = FOLS;
        printf("%s","\v\v\t\tEnter student id\t\t\t\t->\t");
        scanf("%d", &student_id);
        


        // executes when the book exists
        while (!feof(studentPtr))
        {
            int result2 = fread(&student, sizeof(STUDENT), 1, studentPtr);
            if(result2 != 0 && student.id == student_id)
                {
                    // char fname[30] = student.fname;
                    puts("\v\v\t\t______________________________________\n");
                    puts("\t\tproceed, the student id exist");
                    puts("\t\t______________________________________\v\v");
                    y = TRU; // to enable the book to be checked
                }
            
        }

        while (y == TRU)
        {   
            y = FOLS; // to stop the loop
            printf("%s", "\v\v\t\tEnter id of the book to issue\t\t\t->\t");
            // printf("%s", "\t\t(Enter the id here)->\t");                
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
                        printf("\t\tNew record -> \t%-6d%-16s%-11s%u\n", book.id, book.title, 
                            book.author, book.copies);
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

        // executes when the student exists
        if(x == TRU && y == FOLS )
        {
            puts("\v\v\t\t\tstoring the data..\v");
            sleep(1);
            issuedbook.student_id = student_id;
            // issuedbook.fname = student.fname;
            issuedbook.book_id = book_id;
            // issuedbook.title = book.title; 
            fwrite(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);

            // x = FOLS; // just to demonstrate that x changed
            
        }
    
        

            

        puts("\v\v\v\v\v\v\v\v\v\v\t\t####################################################################");
        int choice;
        printf("%s", "\n\t\tEnter 1 to continue or 0 to exit: \n");
        printf("%s", "\v\t\t(Enter your choice here)->\t");
        scanf("%d", &choice);
        if (choice == 1)
        {
            issueBook();
        }

        fclose(bookPtr);
        fclose(studentPtr);
        fclose(issuedBookPtr);
    
        // menu(); // got to the customized view of the librarian

    }
}

void viewIssuedBook(void)
{
    system("clear"); // works only on ubuntu
    puts("\v\t\t\t\t\t\t\t\t```````````````````````````````````");
    
    printf("%s","\t\t\t\t\t\t\t\t\t\033[22;34mLIST OF ISSUED BOOKS\033[0m\n");
    puts("\t\t\t\t\t\t\t\t```````````````````````````````````\v\v\v");

    issuedBookPtr = fopen("issuedBook.dat", "rb");

    if (issuedBookPtr == NULL)
    {
        puts("\v\v\t\tError opening the issuedBook information file");
    }
    else
    {
    
        puts("\v\t\t\t\t\t\t\t\tStudent_id\t\tBook_id");
        puts("\t\t\t\t\t\t\t\t___________________________________\n");

        while (!feof(issuedBookPtr))
        {
            int  result = fread(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);
            if(result != 0 && issuedbook.student_id != 0)
            {
                printf("\t\t\t\t\t\t\t\t  %d  \t\t\t %d\n", issuedbook.student_id, issuedbook.book_id);
                puts("\t\t\t\t\t\t\t\t```````````````````````````````````");
        
            }
        }

        fclose(bookPtr);

        puts("\v");
        int choice;

        printf("\v\v\v\v\v\v\v\t\t\t\t\t\t\t\t######################################\n");
        printf("\t\t\t\t\t\t\t\tEnter 0 to go back to the main menu ->\t");
        // printf("%s", "\t\t(Enter your choice here)->\t");

        scanf("%d", &choice);

        if (choice == 0)
        {
            // goes to the customized librabrian view
        }
    }
}

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

            puts("\v\v\t\t\t\t\t_________________________________________________________________\n");
            printf("\t\t\t\t\t| Old record | -> \t'%-6d%-16s%-11s%u'\n", book.id, book.title, 
                    book.author, book.copies);
            puts("\t\t\t\t\t_________________________________________________________________\v");

            printf("%s", "\v\v\t\t\t\t\tEnter the new title, author and copies (eg c-program chris-o 98)\n\t\t\t\t\t -> \t");
            scanf("%29s%29s",book.title, book.author);

            unsigned int copies;
            scanf("%u", &copies);
            book.copies = copies;

            // set cursor at the begining of the record 
            fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);
            fwrite(&book, sizeof(BOOK), 1, bookPtr);
            puts("\v\v\v\v\t\t\t\t\tRecord is successfully updated ");

            puts("\v\v\t\t\t\t\t_________________________________________________________________\n");
            printf("\t\t\t\t\t| New record | ->\t '%-6d%-16s%-11s%u'\n", book.id, book.title, book.author, book.copies);
            puts("\t\t\t\t\t_________________________________________________________________\v");

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


void deleteBook(void)
{
    system("clear"); // on windows system("cls");
    bookPtr = fopen("books.dat", "rb+");
    issuedBookPtr = fopen("issuedBook.dat", "rb+");


    int count = 0; // to keep track of the record currently read
    char stop = 'n'; // to halt the loop when the record is found
    puts("\v\t\t\t\t\t\t\t\t````````````````````````````````");
    
    puts("\t\t\t\t\t\t\t\t\t\033[22;34mDELETE BOOK\033[0m");
    puts("\t\t\t\t\t\t\t\t````````````````````````````````\v\v");

    // entry of id used for verification
    printf("%s", "\v\v\t\t\t\t\tEnter an id of the book to delete \t\t\t->\t");
    unsigned int book_id;
    scanf("%u", &book_id);


    while (!feof(bookPtr) && stop == 'n')
    {

        BOOK book;
        int  del = 0, result = fread(&book, sizeof(BOOK), 1, bookPtr); // checks if the record is empty
        count += result; // keeps track of the record number currently read

        if ( (result != 0) &&  book.id == book_id  )
        {
            stop = 'y'; // the id exists

            // to ensure borrowed book is not deleted
            while(!feof(issuedBookPtr) && del == 0)
            {
                ISSUEDBOOK issuedbook;

                int result = fread(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);
                    if (result != 0 && book_id == issuedbook.book_id) {
                        puts("\v\v\v\v\t\t\t\t\t________________________________________________________________________________________");
                        puts("\n\t\t\t\t\t\tError: Record of borrowed books can not be deleted until returned");
                        puts("\t\t\t\t\t________________________________________________________________________________________");
                        del = 1;
                    }
            }
            
            // if not borrowed then delete
            while(del == 0 )
            {
                
                del = 1; // to terminate the loop
                // set cursor at the begining of the record 
                fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);
                puts("\v\v\v\v\t\t\t\t\t________________________________________________________________________________________\n");
                printf("\t\t\t\t\tRecord to be deleted -> \t(id)%-6d%-16s %-11s %u\n", book.id, book.title, 
                        book.author, book.copies);
                puts("\t\t\t\t\t________________________________________________________________________________________");
            
                int confirm;
                printf("\v\v\v\t\t\t\t\tConfirm deletion by entering 1 otherwise 0 (then press enter key)\t\t ->\t");
                scanf("%d", &confirm);
                if (confirm == 1) 
                {    
                    BOOK blankbook = {0, 0 ,"", ""};

                    // set cursor at the begining of the record 
                    fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);
                    fwrite(&blankbook, sizeof(BOOK), 1, bookPtr);
                    puts("\v\v\v\v\t\t\t\t\t________________________________________________________________________________________");
                    puts("\n\t\t\t\t\t\t\t\tHurray: Record is successfully deleted ");
                    puts("\t\t\t\t\t________________________________________________________________________________________");
                }
                else
                {
                    puts("\v\v\v\v\t\t\t\t\t________________________________________________________________________________________");
                    printf("\t\t\t\t\tRetained record -> \t%-6d%-16s%-11s%u\n\n", book.id, book.title, 
                        book.author, book.copies);
                    puts("\t\t\t\t\t________________________________________________________________________________________");
                      
                }
                

            }
        }

    }

    // variable stop does not change if the book does not exist
    while(stop == 'n'){
        puts("\v\v\v\v\t\t\t\t\t________________________________________________________________\n");
        puts("\t\t\t\t\t\t\tError: The book id does not exist!");
        puts("\t\t\t\t\t________________________________________________________________");
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
        // menu();
    }
    else
    {
        deleteBook();
    }
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
        char tru = 'y', fols = 'y';
        unsigned int student_id, book_id;
        printf("%s", "\v\v\t\t\tEnter student id \t");
        scanf("%u", &student_id);
        
        printf("%s", "\v\v\t\t\tEnter book id \t");
        scanf("%u", &book_id);


        // delete record from issuedbook list
        int count = 0;
        while(!feof(issuedBookPtr))
        {

            ISSUEDBOOK issuedbook;
            int result = fread(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);
            count += result;

            if (result != 0 && book_id == issuedbook.book_id && student_id == issuedbook.student_id ) 
            {   
                tru = 'n'; // changed when record exists
                fseek(issuedBookPtr, (count - 1)*sizeof(ISSUEDBOOK), SEEK_SET );
                ISSUEDBOOK blankbook = { 0, 0, "", "" };
                fseek(issuedBookPtr, (count - 1)*sizeof(ISSUEDBOOK), SEEK_SET );
                fwrite(&blankbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);
            }
        }
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
                fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);
                ++book.copies;
                fseek(bookPtr, (count - 1)*sizeof(BOOK), SEEK_SET);
                fwrite(&book, sizeof(BOOK), 1, bookPtr);
            }
            
        }
        rewind(bookPtr);
        fclose(bookPtr);

        if (tru == 'n' && fols == 'n') {
            puts("\v\v\t\t\tThe records are successfully updated");
        }
        else if (tru == 'n' && fols == 'y')
        {
            puts("\v\v\t\t\tError: The book id does not exist");
        }
        else if (tru == 'y' && fols == 'n' )
        {
            puts("\v\v\t\t\tError: The records does not exist in the issued books");
        }
        else
        {
            puts("\v\v\t\t\tOops! The system has no records on this book and its lease");
        }

        sleep(3);
        // this goes to the customized view of the librabrian
        // menu();
    }
}


