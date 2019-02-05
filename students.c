#include "structs.c"
typedef struct
{
    unsigned int id, copies;
    char title[30], author[30];
} BOOK2;


typedef struct
{
    // COURSE course;
    // DATE dob;
    unsigned int day, id, month, year ;
    char  fname[30], lname[30];
    char faculty[30], department[30], course_title[30];
} STUDENT2;



void menu(void);

BOOK2 book2;
STUDENT2 student2;
// ISSUEDBOOK2 issuedbook2;
// a function that adds a student2's information
void addStudent(void)
{
    system("clear");  // works only for linux sys

    puts("\v\t\t\t\t\t\tADD STUDENT2");
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
        unsigned int student2_id;
        puts("\v\t\tEnter student id");
        printf("%s","\t\t>");
        scanf("%u", &student2_id);
            
        while (!feof(studentPtr))
        {
            fread(&student2, sizeof(STUDENT2), 1, studentPtr);
            if (student2_id == student2.id)
            {
                puts("\v\t\tError: The student2 id exists");
                sleep(2);
                student2_id = 0 ;
            }
        }

        while (student2_id != 0)
        {
            puts("\t\tEnter the first name and last name");
            printf("%s","\t\t>");
            scanf("%29s%29s",student2.fname, student2.lname);
            
            
            // enter date of birth
            puts("\v\t\tEnter your date of birth: day month year");
            printf("%s","\t\t>");
            // scanf("%d%d%d", &student2.dob.day, &student2.dob.month, &student2.dob.year);
            scanf("%d%d%d", &student2.day, &student2.month, &student2.year);

            // entry of course information
            puts("\v\t\tEnter your faculty, department and course title");
            printf("%s","\t\t>");
            // scanf("%29s%29s%29s", student2.course.faculty, student2.course.department, student2.course.course_title);
            scanf("%29s%29s%29s", student2.faculty, student2.department, student2.course_title);

            while (!feof(studentPtr))
                {
                    fread(&student2, sizeof(STUDENT2), 1, studentPtr);
                    if (student2_id == student2.id)
                    {
                        puts("\v\t\tError: The student2 id exists");
                        sleep(2);
                        student2_id = 0 ;
                    }
                }
            student2.id = student2_id;
            if (student2_id != 0) 
            {
                
            fwrite(&student2, sizeof( STUDENT2 ), 1, studentPtr);
            student2_id = 0;
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

// view all student2s
void viewStudents(void)
{
    system("clear");

    puts("\v\t\t\t\t\t\tLIST OF REGISTERED STUDENT2S:");
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
                int result = fread(&student2, sizeof(STUDENT2), 1, studentPtr);
                if (result != 0 && student2.id != 0)
                {
                    printf("%u%29s%29s\t%u/%u/%u%29s%29s%29s\n",
                    student2.id, student2.fname, student2.lname,
                    student2.day,student2.month,student2.year,
                    student2.faculty,student2.department,student2.course_title
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

