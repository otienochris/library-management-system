void menu(void);


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

}
