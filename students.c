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
                puts("\v\t\tError: The student id exists");
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

void deleteStudent(void)
{
    system("clear");
    studentPtr = fopen("student.dat", "rb+");
    issuedBookPtr = fopen("issuedBook.dat", "rb+");

    if (studentPtr == NULL || issuedBookPtr == NULL ) {
        puts("\v\v\v\t\t\tError: Could not access the required files ");
    }
    else
    {
        
    
    
    int count = 0; // to keep track of the record currently read
    char stop = 'n'; // to halt the loop when the record is found

    // entry of id used for verification
    printf("%s", "\v\v\t\tEnter an id of the book to update ->");
    unsigned int student_id;
    scanf("%u", &student_id);


    while (!feof(studentPtr) && stop == 'n')
    {

        STUDENT2 student2;
        int  del = 0, result = fread(&student2, sizeof(STUDENT2), 1, studentPtr); // checks if the record is empty
        count += result; // keeps track of the record number currently read

        if ( (result != 0) &&  student2.id == student_id  )
        {
            stop = 'y'; // the id exists

            // to ensure that a student2 having a book can not be deleted
            while(!feof(issuedBookPtr))
            {
                ISSUEDBOOK issuedbook;

                int result = fread(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);
                    if (result != 0 && student_id == issuedbook.student_id) {
                        puts("\v\v\v\v\t\t\tError: The student record can not be deleted while having books");
                        del = 1; // ensure no deletion of this record
                        sleep(3);
                    }
            }
            
            // if student2 having no book the delete
            while(del == 0 )
            {
                
                del = 1; // to terminate the loop

                // set cursor at the begining of the record 
                fseek(studentPtr, (count - 1)*sizeof(STUDENT2), SEEK_SET);
              
              printf("%u%29s%29s\t%u/%u/%u%29s%29s%29s\n",
                    student2.id, student2.fname, student2.lname,
                    student2.day,student2.month,student2.year,
                    student2.faculty,student2.department,student2.course_title
                    ); 
            
                STUDENT2 blankstudent = {0, 0, 0 , 0, "", "" ,"", "", ""};


                // set cursor at the begining of the record 
                fseek(studentPtr, (count - 1)*sizeof(STUDENT2), SEEK_SET);
                fwrite(&blankstudent, sizeof(STUDENT2), 1, studentPtr);
                puts("\v\v\v\v\t\tRecord is successfully deleted ");
                

                sleep(3);
            }
        }

    }

    // variable stop does not change if the book does not exist
    while(stop == 'n'){
        puts("\v\v\t\t\tError: The book id does not exist");
        stop = 'y'; // terminate the loop
        sleep(2);
    }
    
    rewind(studentPtr); // returns the cursor to the begining of the file 
    fclose(studentPtr);
    }
    menu();
}

void updateStudent(void)
{
    system("clear");

    studentPtr = fopen("student.dat", "rb+");

    if (studentPtr == NULL) {
        puts("Error: opening the files");
        sleep(2);
    }
    else
    {   
        int count = 0; // to keep track of the record currently read
        char stop = 'n'; // to halt the loop when the record is found

        // entry of id used for verification
        printf("%s", "\v\v\t\tEnter an id of the student to update ->");
        unsigned int student_id;
        scanf("%u", &student_id);


        while (!feof(studentPtr) && stop == 'n')
        {

            STUDENT2 student2;
            int  result = fread(&student2, sizeof(STUDENT2), 1, studentPtr); // checks if the record is empty
            count += result; // keeps track of the record number currently read

            if ( (result != 0) &&  student2.id == student_id  )
                {
                    // set cursor at the begining of the record 
                    fseek(studentPtr, (count - 1)*sizeof(STUDENT2), SEEK_SET);
                    
                    printf("%s", "\v\v\t\tEnter the first name and last name");
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

                    // set cursor at the begining of the record 
                    fseek(studentPtr, (count - 1)*sizeof(STUDENT2), SEEK_SET);
                    fwrite(&student2, sizeof(STUDENT2), 1, studentPtr);
                    puts("\v\v\v\v\t\tRecord is successfully update ");
                    puts("\v\v\v\t\t\tNew record");
                    printf("%u%29s%29s\t%u/%u/%u%29s%29s%29s\n",
                            student2.id, student2.fname, student2.lname,
                            student2.day,student2.month,student2.year,
                            student2.faculty,student2.department,student2.course_title
                            );

                    stop = 'y'; // terminate the loop
                    sleep(2);
                }

            }

        // variable stop does not change if the book does not exist
        while(stop == 'n'){
            puts("\v\v\t\t\tError: The book id does not exist");
            stop = 'y'; // terminate the loop
            sleep(2);
        }
        
        rewind(studentPtr); // returns the cursor to the begining of the file 
        fclose(studentPtr);
    }
    menu();
}
