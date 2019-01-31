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

    bookPtr = fopen("books.dat","ab+");
    
    if (bookPtr == NULL)
    {
        puts("Error opening books.dat");
        exit(1);
    }
    else
    {
        puts("Enter the id, title, author and copies");
        printf("%s",">");
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


// a function that adds a student's information
void addStudent(void)
{
    system("clear");  // works only for linux sys

    studentPtr = fopen("student.dat", "ab+");

    if (studentPtr == NULL)
    {
        puts("Error opening students.dat");
        exit(1);
    }
    else
    {
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
    
}

// view all students
void viewStudents(void)
{

}

void viewBooks(void)
{

    bookPtr = fopen("books.dat", "rb");

    if (bookPtr == NULL)
    {
        puts("Error opening the book.dat file");
    }
    else
    {
        puts("Book_id\tTitle\tAuthor\tCopies");
        while (!feof(bookPtr))
        {
            int  result = fread(&book, sizeof(BOOK), 1, bookPtr);
            if(result != 0 && book.id != 0)
            {
                printf("%d\t%s\t%s\t%d\n", book.id, book.title, book.author, book.copies);
            }
        }

        fclose(bookPtr);

    }
}