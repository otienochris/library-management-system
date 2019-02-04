void menu(void);

BOOK book;
STUDENT student;
ISSUEDBOOK issuedbook;
// a function that adds a student's information
void addStudent(void)
{
    system("clear");  // works only for linux sys

    puts("\v\t\t\t\t\t\tADD STUDENT");
    puts("\t\t\t\t\t____________________________\v\v");

    puts("\t\tmultiple names must be separated using a hyphen(eg c-programming otieno-chris 900)");


    studentPtr = fopen("student.dat", "a+");

    if (studentPtr == NULL)
    {
        puts("Error opening students.dat");
        exit(1);
    }
    else
    {
        unsigned int student_id;
        puts("\v\t\tEnter student id");
        printf("%s","\t\t>");
        scanf("%u", &student_id);
            
        while (!feof(studentPtr))
        {
            fread(&student, sizeof(STUDENT), 1, studentPtr);
            if (student_id == student.id)
            {
                puts("\v\t\tError: The student id exists");
                sleep(2);
                student_id = 0 ;
            }
        }

        while (student_id != 0)
        {
            puts("\t\tEnter the first name and last name");
            printf("%s","\t\t>");
            scanf("%29s%29s",student.fname, student.lname);
            
            
            // enter date of birth
            puts("\v\t\tEnter your date of birth: day month year");
            printf("%s","\t\t>");
            // scanf("%d%d%d", &student.dob.day, &student.dob.month, &student.dob.year);
            scanf("%d%d%d", &student.day, &student.month, &student.year);

            // entry of course information
            puts("\v\t\tEnter your faculty, department and course title");
            printf("%s","\t\t>");
            // scanf("%29s%29s%29s", student.course.faculty, student.course.department, student.course.course_title);
            scanf("%29s%29s%29s", student.faculty, student.department, student.course_title);

            while (!feof(studentPtr))
                {
                    fread(&student, sizeof(STUDENT), 1, studentPtr);
                    if (student_id == student.id)
                    {
                        puts("\v\t\tError: The student id exists");
                        sleep(2);
                        student_id = 0 ;
                    }
                }
            student.id = student_id;
            if (student_id != 0) 
            {
                
            fwrite(&student, sizeof( STUDENT ), 1, studentPtr);
            student_id = 0;
            }

        }
            printf("%s", "\v\t\trestart the program to view changes in the files...\n");
            sleep(2);
            
            puts("\v");
            
            int choice;
            printf("\v\v\v\v\v\v\v\t\t\tEnter 0 to go back to the main menu (press 1 continue)");
            printf("%s", "\t\t(Entery goes here)->\t");

            scanf("%d", &choice);

            if (choice == 0)
            {
                menu();
            }
            else
            {
                addStudent();
            }
        fclose(studentPtr);
        menu();
    }

}

// view all students
void viewStudents(void)
{
    system("clear");

    puts("\v\t\t\t\t\t\tLIST OF REGISTERED STUDENTS:");
    puts("\t\t\t\t\t\t____________________________\v\v");

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
            printf("%s", "\t\t(Entery goes here)->\t");

            scanf("%d", &choice);

            if (choice == 0)
            {
                menu();
            }
}

