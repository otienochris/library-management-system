void menu(void);

BOOK book;
STUDENT student;
ISSUEDBOOK issuedbook;
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
        scanf("%u%29s%29s", &student.id, student.fname, student.lname);

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
            scanf("%u%29s%29s", &student.id, student.fname, student.lname);
        }
        fclose(studentPtr);
    }
    menu();
}

// view all students
void viewStudents(void)
{
system("clear");

puts("\v\t\t\t\t\t\tLIST OF REGISTERED STUDENTS:");
puts("\t\t\t\t\t\t____________________________:\v\v");

studentPtr = fopen("student.dat", "rb");

if (studentPtr == NULL)
{
   puts("\v\t\tError: Could not open the students record"); 
}
else
    {
        puts("id\t\t\tfirstName\t\t   lastName     D.O.B\t\t\t\tfaculty\t\t\tdepart't\t\t\tcourse");
        puts("______________________________________________________________________________________________________________________________________________________________________\v");
        while (!feof(studentPtr))
        {
            int result = fread(&student, sizeof(STUDENT), 1, studentPtr);
            if (result != 0 && student.id != 0)
            {
                printf("%u%29s%29s\t%u/%u/%u%29s%29s%29s\n",
                student.id, student.fname, student.lname,
                student.day,student.month,student.year,
                student.faculty,student.department,student.course_title
                );    
            }
            
        }
        fclose(studentPtr);
        
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
