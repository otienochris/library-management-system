
//  global pointer
FILE *bookPtr, *studentPtr, *userPtr;


// a function that adds a book(s) to books.bin file
void addBook(void)
{
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
    }
}


// a function that adds a student's information
void addStudent(void)
{
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
    }
}


