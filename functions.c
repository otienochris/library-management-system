void menu(void);
//  global pointer
FILE *bookPtr, *studentPtr, *userPtr;


// a function that adds a book(s) to books.bin file
void addBook(void)
{
    system("clear");    // works only for linux sys

    bookPtr = fopen("books.bin","ab+");
    
    if (bookPtr == NULL)
    {
        puts("Error opening books.bin");
        exit(1);
    }
    else
    {
        BOOK book ;
        // = {0, "", "", 0}
        puts("Enter the id, title, author and copies");
        while (!feof(stdin))
        {
            printf("%s",">");
            scanf("%u%29s%29s%u", &book.id, book.title, book.title, &book.copies);
            fwrite(&book, sizeof( BOOK ), 1, bookPtr);  
        }
        fclose(bookPtr);
    }
    menu();
}


// a function that adds a student's information
void addStudent(void)
{
    system("clear");  // works only for linux sys

    studentPtr = fopen("student.bin", "ab+");

    if (studentPtr == NULL)
    {
        puts("Error opening students.bin");
        exit(1);
    }
    else
    {
        STUDENT student;
            puts("Enter the id, first name and last name");
            printf("%s",">");
            scanf("%29s%29s%29s", student.id, student.fname, student.lname);
        while (!feof(stdin))
        {
            
            // enter date of birth
            puts("Enter your date of birth: day month year");
            printf("%s",">");
            // scanf("%d%d%d", &student.dob.day, &student.dob.month, &student.dob.year);
            scanf("%d%d%d", &student.day, &student.month, &student.year);

            // entry of course information
            puts("Enter your faculty, department and course title");
            printf("%s",">");
            // scanf("%29s%29s%29s", student.course.faculty, student.course.department, student.course.course_title);
            scanf("%29s%29s%29s", student.faculty, student.department, student.course_title);
            fwrite(&student, sizeof( STUDENT ), 1, studentPtr);

            puts("Enter the id, first name and last name");
            printf("%s",">");
            scanf("%29s%29s%29s", student.id, student.fname, student.lname);
        }
        fclose(studentPtr);
    }
    menu();
}

// search for a book
void searchBook(void)
{
    system("clear");    // works only for linux sys

    FILE *bookPtr;
    BOOK book;

    char search_title[30];
    unsigned int search_id;

    bookPtr = fopen("books.bin", "r");
    fread(&book, sizeof(BOOK), 1, bookPtr);

    if (bookPtr == NULL)
    {
        puts("Error opening the books.bin file");
    }
    else
    {   
        unsigned int entry;
        puts("Enter 1 to search using book id or "
            "Enter 2 to search using book title");
        scanf("%u", &entry);
        if (entry == 1)
        {
            puts("Enter book id to search:");
            scanf("%u", &search_id);
            if ( search_id == book.id)
            {
                printf("%ls%29s\n", &book.id, book.title);                
            }
            else
            {
                puts("The id entered is not valid");
            }
        }
        else if
        {
            
            puts("Enter the book title that you want to search for:");
            scanf("%29s", search_title);
            if ( search_title == book.title )
            {
                printf("%ls%29s\n", &book.id, book.title);
            }
            else
            {
                puts("The title entered is not valid");                
            }
        }
    fclose(bookPtr);
    }
    menu();

}


void menu(void)
{
    system("clear");    // works only for linux sys

    int choice;

    puts("1 -> Add student\n"
        "2 -> add Book\n"
        "3 -> search for a Book\n"
        "4 -> exit the program");
    printf("%s", ">");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        addStudent();
        break;
    case 2:
        addBook();
        break;
    case 3:
        searchBook();
        break;
    case 4:
        puts("Thanks for spending time here.");
        exit(1);

    default:
        puts("Invalid entry");
        menu();
        break;
    }

}