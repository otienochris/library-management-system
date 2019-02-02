void menu(void);

//  global pointer
FILE *bookPtr, *studentPtr, *userPtr;

// global struct declaration
BOOK book;
STUDENT student;

// a function that adds a book(s) to books.dat file    
void addBook(void)
{
    int book_id;

    bookPtr = fopen("books.dat", "a+");
    
    printf("%s", "\v\t\tEnter book id: ");
    scanf("%d", &book_id);
        
            
        while (!feof(bookPtr))
        {
            fread(&book, sizeof(BOOK), 1, bookPtr);
            if (book_id == book.id)
            {
                puts("Error: The book id exists");
                sleep(1);
                book_id = 0 ;
            }
        }


        
        // printf("%s", "\v\t\tEnter book id (integers): ");
        // scanf("%d", &book.id);

        while (book_id != 0){
            book.id = book_id;
            printf("%s", "\n title, author and copies");

            fscanf(stdin, "%14s%9s%d", book.title, book.author, &book.copies);

            // fseek(bookPtr, (book.id - 1)* sizeof(BOOK), SEEK_SET);
         
            fwrite(&book, sizeof(BOOK), 1, bookPtr);

            int choice;
            printf("%s", "\n\t\tEnter 1 to continue or 0 to exit:  ");
            scanf("%d", &choice);
            
            if (choice == 1)
            {
                addBook();
            }
            else
            {
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
        
        printf("%s", "\v\t\t1 -> Search by title:\n "
                "\t\t2 -> search by id:\v");
        scanf("%d", &choice);

        switch(choice){
            case 1:

                puts("\n\t\tEnter the title of the book to search:");
                printf("%s","\t\t>");
                scanf("%29s", search_title);

                puts("\v\t\tBook_id\t\tTitle\t\tAuthor\t\tCopies");            
                while (!feof(stdin))
                {
                    
                while (!feof(bookPtr))
                {
                    int  result = fread(&book, sizeof(BOOK), 1, bookPtr);

                    if ((strcmp(book.title, search_title)==0) && (result != 0) )
                        {
                        printf("\v\t\t%d\t\t%s\t\t%s\t\t%d\n", book.id, book.title, book.author, book.copies);
                        }

                }
                
                // puts("\n\t\tSearch for another book: ");
                puts("\v\v\t\tTo Exit to main menu press: \n\t\tctrl+D (linux) or ctrl+Z(windows)");
                printf("%s","\t\t>");
                scanf("%29s", search_title);
                }
                break;

            case 2:
                puts("\n\t\tEnter the id of the book to search:");
                printf("%s","\t\t>");
                scanf("%u", &search_id);

                puts("\v\t\tBook_id\t\tTitle\t\tAuthor\t\tCopies");            
                while (!feof(stdin))
                {
                    
                while (!feof(bookPtr))
                {
                    int  result = fread(&book, sizeof(BOOK), 1, bookPtr);

                    if ( (result != 0) &&  book.id == search_id  )
                        {
                        printf("\v\t\t%d\t\t%s\t\t%s\t\t%d\n", book.id, book.title, book.author, book.copies);
                        }

                }
                
                // puts("\n\t\tSearch for another book: ");
                puts("\v\v\v\v\v\v\v\t\tTo Exit to main menu press: \n\t\tctrl+D (linux) or ctrl+Z(windows)");
                printf("%s","\t\t>");
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
    system("clear");

    puts("\t\t\t\tLIST OF BOOKS:");
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
            int  result = fread(&book, sizeof(BOOK), 1, bookPtr);
            if(result != 0 && book.id != 0)
            {
                printf("\n\t\t\t%d\t\t\t%s\t\t\t%s\t\t\t%d\n", book.id, book.title, book.author, book.copies);
            }
        }

        fclose(bookPtr);

    }
    puts("\v");
    int menu1;
    printf("\t\tEnter 0 to go back to the main menu\t");
    scanf("%d", &menu1);

    if (menu1 == 0)
    {
        menu();
    }
}

void issueBook(void)
{
    bookPtr = fopen("books.dat","rb+");
    puts("\v\t\tISSUE BOOK:\v");

    // users entry
    int book_id;
    printf("%s","Enter book id:\t");
    scanf("%d", &book_id);
    // temp = book_id;

    if (bookPtr == NULL)
    {
        puts("Error: The file could not be oppened");
    }
    else
    {
        while (!feof(bookPtr))
        {
            if (book.id == book_id)
            {
                book_id = 0;
            }        
        }

        while (book_id != 0)
        {
            
        }





    }
}