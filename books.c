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
        puts("\t\tEnter the id, title, author and copies");
        printf("%s","\t\t>");
        scanf("%u%29s%29s%u", &book.id, book.title, book.author, &book.copies);

        while (!feof(stdin))
        {
            printf("%s",">");
            fwrite(&book, sizeof( BOOK ), 1, bookPtr);  
            scanf("%u%29s%29s%u", &book.id, book.title, book.author, &book.copies);
        }
        fclose(bookPtr);
    }
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

        while (!feof(stdin))
        {
            int  result = fread(&book, sizeof(BOOK), 1, bookPtr);
            if(result != 0 && book.id != 0)
            {
                // book.title && search_title
                if (strcmp(book.title, search_title)==0)
                {
                printf("\t\t%d\t\t%s\t\t%s\t\t%d\n", book.id, book.title, book.author, book.copies);
                }
                    
            }
        }

        fclose(bookPtr);
    }
    menu();
}


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