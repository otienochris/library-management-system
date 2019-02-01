void menu(void);

//  global pointer
FILE *bookPtr, *studentPtr, *userPtr;

// global struct declaration
BOOK book;
STUDENT student;


// a function that adds a book(s) to books.dat file
void addBook(void)
{
    system("clear");    // works only for linux sys


    puts("\t\tADD BOOK:");
    bookPtr = fopen("books.dat","ab+");
    
    if (bookPtr == NULL)
    {
        puts("Error opening books.dat");
        exit(1);
    }
    else
    {
        unsigned int book_id;
        printf("%s", "\t\tEnter book_id: ");
        scanf("%u", &book_id);

        while (!feof(bookPtr))
        {
            fread(&book, sizeof(BOOK), 1, bookPtr);
            if (book.id == book_id)
                {
                    puts("\v\t\tError: The id exist!");
                    sleep(1);
                    menu();
                }
        }
                
        puts("\t\tEnter the title, author and copies");
        printf("%s","\t\t>");
        scanf("%29s%29s%u", book.title, book.author, &book.copies);

        book.id = book_id;
        while (!feof(stdin))
        {
            printf("%s",">");
            fwrite(&book, sizeof( BOOK ), 1, bookPtr);  
            scanf("%29s%29s%u", book.title, book.author, &book.copies);
        }
        }
        fclose(bookPtr);

        menu();
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

        char search_title[30];
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
        puts("\v\t\tTo Exit to main menu press: \n\t\tctrl+D (linux) or ctrl+Z(windows)");
        printf("%s","\t\t>");
        scanf("%29s", search_title);
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
        puts("\v\t\tBook_id\t\tTitle\t\tAuthor\t\tCopies");
        while (!feof(bookPtr))
        {
            int  result = fread(&book, sizeof(BOOK), 1, bookPtr);
            if(result != 0 && book.id != 0)
            {
                printf("\n\t\t%d\t\t%s\t\t%s\t\t%d\n", book.id, book.title, book.author, book.copies);
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

void validatedBookId(void)
{
    bookPtr = fopen("books.dat","ab+");

    unsigned int book_id;
    printf("%s", "\n\t\tEnter id: ");
    scanf("%u", &book_id);

    while(!feof(bookPtr)){

        fread(&book, sizeof(BOOK), 1, bookPtr);
        unsigned int bookie = book.id;
        
        if (bookie == book_id)
        {
            system("clear");
            puts("Error: The id exists");
            menu();    
        }
        else
        {
            addBook();
        }
    }
    fclose(bookPtr);
}