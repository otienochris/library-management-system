// #include "structs.c"
typedef struct
{
    unsigned int id, copies, rack, pub_year;
    char title[30], author[30], publisher[30], edition[5];
} BOOK2;


typedef struct
{
    unsigned int day, id, month, year ;
    char  fname[30], lname[30];
    char faculty[30], department[30], course_title[30];
} STUDENT2;



void menu(void);
int main();

BOOK2 book2;
STUDENT2 student2;

// a function that adds a student2's information
void addStudent(void)
{
    system("clear"); // works on linux (comment this line while using windows)
    // system("cls")  // uncomment this line while on windows

    puts("\v\t\t\t\t\t\t\t\t````````````````````````````````");
    puts("\t\t\t\t\t\t\t\t\t   \033[22;34mADD STUDENT\033[0m\n");
    puts("\t\t\t\t\t\t\t\t````````````````````````````````\v\v");

    puts("\v\v\v\v\t\t\t\t\t________________________________________________________________________________________\n");
    puts("\t\t\t\t\t  *Multiple names must be separated using a hyphen(eg c-programming otieno-chris )\n");
    puts("\t\t\t\t\t  *In every step, insert the requred records in the same line, values seperated by a\n\t\t\t\t\t   space then press Enter.");
    puts("\t\t\t\t\t________________________________________________________________________________________");


    studentPtr = fopen("student.dat", "a+");

    if (studentPtr == NULL)
    {
        puts("\v\v\v\t\t\tError opening students.dat");
        exit(1);
    }
    else
    {
        unsigned int student2_id;
        printf("\v\v\t\t\t\t\tEnter student id\t\t\t\t\t->\t");
        // printf("%s","\t\t>");
        scanf("%u", &student2_id);
        char info = 'n'; // give info if process success
            
        while (!feof(studentPtr) && student2_id != 0)
        {
            fread(&student2, sizeof(STUDENT2), 1, studentPtr);
            if (student2_id == student2.id)
            {
                puts("\v\v\v\v\t\t\t\t\t________________________________________________________________________________________\n");
                puts("\t\t\t\t\t  Error: The student id exists");
                puts("\t\t\t\t\t________________________________________________________________________________________\n");

                student2_id = 0 ;
            }
        }

        while (student2_id != 0)
        {
            info = 'y';

            printf("\v\v\t\t\t\t\tEnter the first name and last name\t\t\t->\t");
            scanf("%29s%29s",student2.fname, student2.lname);
            
            // enter date of birth
            printf("\v\v\t\t\t\t\tEnter your date of birth: day month year (12 12 2019)\t->\t");
            scanf("%d%d%d", &student2.day, &student2.month, &student2.year);

            // entry of course information
            printf("\v\v\t\t\t\t\tEnter your faculty, department and course title\t\t->\t");
            scanf("%29s%29s%29s", student2.faculty, student2.department, student2.course_title);
           
            // use the entered student id 
            student2.id = student2_id;
            if (student2_id != 0) 
            {
                
            // write the details to the file
            fwrite(&student2, sizeof( STUDENT2 ), 1, studentPtr);
            student2_id = 0;
            }

        }

        // a success message
        if (info == 'y') 
        {
            puts("\v\v\v\v\t\t\t\t\t________________________________________________________________________________________\n");
            printf("%s", "\t\t\t\t\t *The record is successfully saved.\n\n");
            puts("\t\t\t\t\t________________________________________________________________________________________\n");
        } 
        fclose(studentPtr);
            
        puts("\v");
        
        int choice;
        puts("\v\v\v\v\v\v\v\t\t\t\t\t#######################################################################################");
        printf("\t\t\t\t\t\t  Enter 0 to go back to the main menu (press 1 continue)\t->\t");
        // printf("%s", "\t\t(Entery goes here)->\t");

        scanf("%d", &choice);

        if (choice == 0)
        {
            // this goes to the customized view of the librabrian
            // main();
        }
        else
        {
            addStudent();
        }
    }

}

// view all student2s
void viewStudents(void)
{
    system("clear"); // works on linux (comment this line while using windows)
    // system("cls")  // uncomment this line while on windows

    puts("\v\t\t\t\t\t\t\t\t\t````````````````````````````````");
    puts("\t\t\t\t\t\t\t\t\t   \033[22;34mA LIST OF ALL STUDENTS\033[0m\n");
    puts("\t\t\t\t\t\t\t\t\t````````````````````````````````\v\v");

    studentPtr = fopen("student.dat", "rb+");

    if (studentPtr == NULL)
    {
    puts("\v\t\tError: Could not open the students record"); 
    }
    else
        {
            puts("\t id\t\tfirstName\t\t  lastName   \t\t\t\t D.O.B\t\tfaculty   \t\t     department\t\t\tcourse");
            puts("\t_____________________________________________________________________________________________________________________________________________________________________________________________\v");
            
            while (!feof(studentPtr))
            {
                int result = fread(&student2, sizeof(STUDENT2), 1, studentPtr);
                if (result != 0 && student2.id != 0)
                {
                    printf(" \t%-15u%-29s%-29s\t%2u/%2u/%-4u\t%-29s%-29s%-29s\n",
                    student2.id, student2.fname, student2.lname,
                    student2.day,student2.month,student2.year,
                    student2.faculty,student2.department,student2.course_title
                    );  
                    puts("\t`````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````\n");

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
                // this goes to the customized view of the librabrian
            }
}

// a function used to delete a student record 
void deleteStudent(void)
{
    system("clear"); // works on linux (comment this line while using windows)
    // system("cls")  // uncomment this line while on windows

    puts("\v\t\t\t\t\t\t\t\t````````````````````````````````");
    puts("\t\t\t\t\t\t\t\t\t\033[22;34mDELETE STUDENT\033[0m"); // colour blue text
    puts("\t\t\t\t\t\t\t\t````````````````````````````````\v\v");

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
        printf("%s", "\v\v\t\t\t\t\tEnter an id of the student to delete ->");
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


                // to ensure that a student having a book is not to be deleted
                while(!feof(issuedBookPtr) && del == 0)
                {
                    ISSUEDBOOK issuedbook;

                    // read the whole (single) record
                    int result = fread(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);
                        if (result != 0 && student_id == issuedbook.student_id) {
                            puts("\v\v\v\v\t\t\t\t\t________________________________________________________________________________________");
                            puts("\n\t\t\t\t\t Error: The student record can not be deleted while having books\n");
                            puts("\t\t\t\t\t________________________________________________________________________________________");
                            del = 1; // ensure no deletion of this record and to stop the search
                            sleep(3);
                        }
                }
                fclose(issuedBookPtr); // closes the issued books' records
                
                // if student has no book then delete their record
                while(del == 0 )
                {
                    
                    del = 1; // to terminate the loop

                    // set cursor at the begining of the record 
                    fseek(studentPtr, (count - 1)*sizeof(STUDENT2), SEEK_SET);
                    puts("\v\v\t id\t\tfirstName\t\t  lastName   \t\t\t\t D.O.B\t\tfaculty   \t\t     department\t\t\tcourse");
                    puts("\t_____________________________________________________________________________________________________________________________________________________________________________________________\v");
                
                    printf(" \t%-15u%-29s%-29s\t%2u/%2u/%-4u\t%-29s%-29s%-29s\n",
                        student2.id, student2.fname, student2.lname,
                        student2.day,student2.month,student2.year,
                        student2.faculty,student2.department,student2.course_title
                        ); 
                    puts("\t__________________________________________________________________________________________________________________________________________________________________");
                
                    // confirmation message for deletion
                    int confirm;
                    printf("\v\v\v\t\t\t\t\tConfirm deletion by entering 1 otherwise 0 (then press enter key)\t\t ->\t");
                    scanf("%d", &confirm);
                    if (confirm == 1) 
                    { 
                        STUDENT2 blankstudent = {0, 0, 0 , 0, "", "" ,"", "", ""};


                        // set cursor at the begining of the record 
                        fseek(studentPtr, (count - 1)*sizeof(STUDENT2), SEEK_SET);
                        fwrite(&blankstudent, sizeof(STUDENT2), 1, studentPtr);
                        puts("\v\v\v\v\t\t\t\t\t________________________________________________________________________________________");
                        puts("\t\t\t\t\t  Record is successfully deleted ");
                        puts("\t\t\t\t\t________________________________________________________________________________________");
                        sleep(2);
                    }
                    else
                    {
                        puts("\v\v\v\v\t\t\t\t\t________________________________________________________________________________________");
                        printf("\t\t\t\t\tRetained record \n");
                        puts("\t\t\t\t\t________________________________________________________________________________________");
                        sleep(2);
                    }
                    
                }
            }

        }
        
        rewind(studentPtr); // returns the cursor to the begining of the file 
        fclose(studentPtr); // close the students' info file

        // variable stop does not change if the book does not exist
        while(stop == 'n')
        {
            puts("\v\v\t\t\tError: The book id does not exist");
            stop = 'y'; // terminate the loop
            sleep(2);
        }
    }

}

// a function used to update a student record except the id
void updateStudent(void)
{
    system("clear"); // works on linux (comment this line while using windows)
    // system("cls")  // uncomment this line while on windows

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
        rewind(studentPtr); // returns the cursor to the begining of the file 
        fclose(studentPtr);

        // variable stop does not change if the book does not exist
        while(stop == 'n'){
            puts("\v\v\t\t\tError: The student id does not exist");
            stop = 'y'; // terminate the loop
            sleep(2);
        }
        
    }
    
}

// a function used to search for a student's record
void searchStudent(void)
{
    system("clear"); // works on linux (comment this line while using windows)
    // system("cls")  // uncomment this line while on windows


    puts("\v\t\t\t\t\t\t\t\t\t\t````````````````````````");
    
    puts("\t\t\t\t\t\t\t\t\t\t  \033[22;34mSEARCH FOR STUDENTS\033[0m");
    puts("\t\t\t\t\t\t\t\t\t\t........................\v\v\v\v");
    studentPtr = fopen("student.dat", "rb+");

    if (studentPtr == NULL)
    {
        puts("\v\v\v\t\t\tError opening the student information file");
    }
    else
    {
        unsigned int search_id;
        char search_fname[30], stop_search = 'n';
        int choice;

        printf("%s", "\v\t\t\t\t\t\t________________________________________________________________________________________\n\n"
                "\t\t\t\t\t\t\t|1| Search by fname\t\t<-- or -->\t\t|2| Search by id\n"
                "\t\t\t\t\t\t________________________________________________________________________________________\n"
                );
        printf("%s", "\v\v\t\t\t\t\t\t(Enter your choice here)\t\t\t\t->\t");

        scanf("%d", &choice);

        switch(choice){
            case 1:

                printf("%s","\v\v\n\t\t\t\t\t\tEnter the fname of the student to search:\t\t->\t");
                scanf("%29s", search_fname);

                puts("\v\v\t_____________________________________________________________________________________________________________________________________________________________________________________________\v");
                puts("\t id\t\tfirstName\t\t  lastName   \t\t\t\t D.O.B\t\tfaculty   \t\t     department\t\t\tcourse");
                puts("\t_____________________________________________________________________________________________________________________________________________________________________________________________\v");
            
                while (!feof(studentPtr) && stop_search == 'n')
                {
                    STUDENT student2;
                    int  result = fread(&student2, sizeof(STUDENT), 1, studentPtr);
                    
                    if ((strcmp(student2.fname, search_fname)==0) && (result != 0) )
                        {
                            printf(" \t%-15u%-29s%-29s\t%2u/%2u/%-4u\t%-29s%-29s%-29s\n",
                                    student2.id, student2.fname, student2.lname,
                                    student2.day,student2.month,student2.year,
                                    student2.faculty,student2.department,student2.course_title
                                    );  
                            puts("\t`````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````\n");

                        stop_search = 'y'; // stops the search when student is found
                        }

                }
                puts("\v");
                int choice;
                puts("\v\v\v\v\v\v\v\t\t\t\t\t\t##########################################################################################");
                printf("\t\t\t\t\t\tEnter 0 to go back to the main menu");
                printf("%s", "\t\t(Enter your choice here)->\t");

                scanf("%d", &choice);

                if (choice == 0)
                {
                    // go to the customized view
                }
                
                
                break;

            case 2:
                
                printf("%s","\v\v\n\t\t\t\t\t\tEnter the id of the student to search:\t\t\t->\t");
                scanf("%d", &search_id);
                puts("\v\v\t_____________________________________________________________________________________________________________________________________________________________________________________________\v");
                puts("\t id\t\tfirstName\t\t  lastName   \t\t\t\t D.O.B\t\tfaculty   \t\t     department\t\t\tcourse");
                puts("\t_____________________________________________________________________________________________________________________________________________________________________________________________\v");
            
              
                while (!feof(studentPtr) && stop_search == 'n')
                {
                    STUDENT student2;
                    int  result = fread(&student2, sizeof(STUDENT), 1, studentPtr);
                    
                    if ( student2.id == search_id && (result != 0) )
                        {
                            printf(" \t%-15u%-29s%-29s\t%2u/%2u/%-4u\t%-29s%-29s%-29s\n",
                                    student2.id, student2.fname, student2.lname,
                                    student2.day,student2.month,student2.year,
                                    student2.faculty,student2.department,student2.course_title
                                    );  
                            puts("\t`````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````\n");

                        stop_search = 'y'; // stops the search when student found
                        
                        }

                }
                
                puts("\v");

                int choice2;
                puts("\v\v\v\v\v\v\v\t\t\t\t\t\t##########################################################################################");
                printf("\t\t\t\t\t\tEnter 0 to go back to the main menu");
                printf("%s", "\t\t(Enter your choice here)->\t");

                scanf("%u", &choice2);

                if (choice2 == 0)
                {
                    // go to the customized view                    
                }

        }


        fclose(studentPtr);
        // go to the customized view

        }
}

// a function that displays the student's info and books they borrowed
void accountDetails(int SIZE, unsigned int id, char fname[SIZE])
{
    system("clear"); // works on linux (comment this line while using windows)
    // system("cls")  // uncomment this line while on windows

    puts("\v\v\v\t\t\t\t\t\t\t\t\t```````````````````````````````````````` ");
    puts("\t\t\t\t\t\t\t\t\t\t\033[22;34mACCOUNT DETAILS\033[0m\v");
    puts("\t\t\t\t\t\t\t\t\t```````````````````````````````````````` \v\v\v\v\v\v");

    studentPtr = fopen("student.dat", "rb+");
    issuedBookPtr = fopen("issuedBook.dat", "rb+");
    bookPtr = fopen("books.dat", "rb+");
    if (studentPtr == NULL) {
        puts("\v\v\t\t\tError: Could not open the required files!");
    }
    else
    {
        
        char student_found = 'n';
        // char book_found = 'n';
       while (!feof(studentPtr) && student_found == 'n')
        {
            STUDENT student2;
            int  result = fread(&student2, sizeof(STUDENT), 1, studentPtr);
            
            if (student2.id != 0 && student2.id == id && strcmp(student2.fname, fname) == 0 && (result != 0) )
                    { 
                    puts("\v\t\t****************************************");
                    puts("\t\t\t\033[22;34mBios info:\033[0m\v");
                    puts("\t\t****************************************");
                    puts("\v\t\t__________________________________________________________________________________________________________________________________________________________________\v");
                    puts("\t\t\t   id\t\tfirstName\t\t      lastName   \t\t\tD.O.B");
                    puts("\t\t__________________________________________________________________________________________________________________________________________________________________\v");
                    
                    printf("\t\t\t  %-15u%-29s%-29s\t%u/%u/%u\n",
                        student2.id, student2.fname, student2.lname,
                        student2.day,student2.month,student2.year
                        );
                    puts("\v\t\t```````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````");

                    puts("\v\v\t\t****************************************");
                    puts("\t\t\t\033[22;34mEducation info:\033[0m\v");
                    puts("\t\t****************************************");
                    puts("\v\v\t\t__________________________________________________________________________________________________________________________________________________________________\v");
                    printf("\t\t\tfaculty   \t\t    depart't\t\t\tcourse\n");
                    puts("\t\t__________________________________________________________________________________________________________________________________________________________________\v");
                    printf("\t\t\t%-29s%-29s%-29s\n",student2.faculty,student2.department,student2.course_title);
                         
                puts("\v\t\t```````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````");
                student_found = 'y'; // stops the search when student found
                
                }

        }



        puts("\v\v\v\t\t\t\t\t\t\t\t\t**************************************** ");
        puts("\t\t\t\t\t\t\t\t\t\t\033[22;34mBORROWED BOOKS\033[0m\v");
        puts("\t\t\t\t\t\t\t\t\t**************************************** ");

        puts("\v\v\t\t\t\t\t\t___________________________________________________________________________________");    
        puts("\v\t\t\t\t\t\t\tBook_id  \t\tFrom\t\t  To");
        puts("\t\t\t\t\t\t___________________________________________________________________________________");    

        // checks if the user borrowed a book
        while(!feof(issuedBookPtr))
        {
            ISSUEDBOOK issuedbook;
            int result = fread(&issuedbook, sizeof(ISSUEDBOOK), 1, issuedBookPtr);

            // checks for matching student id
            if (result != 0 && issuedbook.student_id == id) 
            {
                printf("\n\t\t\t\t\t\t\t%-10d", issuedbook.book_id);
                printf("\t\t%2d/%2d/%-4d",issuedbook.date.b_day,issuedbook.date.b_month,issuedbook.date.b_year);
                printf("\t%2d/%2d/%-4d\n",issuedbook.date.r_day, issuedbook.date.r_month, issuedbook.date.r_year);
                puts("\t\t\t\t\t\t```````````````````````````````````````````````````````````````````````````````````");    
            }
        }
        puts("\t\t\t\t\t\t___________________________________________________________________________________");    
        puts("\t\t\t\t\t\t  NB: To view the books details, search using the book id ");
        puts("\t\t\t\t\t\t___________________________________________________________________________________");    


    }
            
    fclose(bookPtr);
    fclose(studentPtr);
    fclose(issuedBookPtr);
            
            
    puts("\v");

    int choice2;
    puts("\v\v\v\v\v\v\v\t\t\t\t\t\t##########################################################################################");
    printf("\t\t\t\t\t\tEnter 0 to go back to the main menu");
    printf("%s", "\t\t(Enter your choice here)->\t");

    scanf("%u", &choice2);

    if (choice2 == 0)
    {
        // go to the customized view                    
    }
}

// a function used by a student to check for their log in details when they forget
void passReset(int SIZE, char lname[SIZE], unsigned int day,unsigned int month,unsigned int year)
{
    system("clear"); // works on linux (comment this line while using windows)
    // system("cls")  // uncomment this line while on windows

    puts("\v\t\t\t\t\t\t\t\t\t````````````````````````````````");
    puts("\t\t\t\t\t\t\t\t\t\t   \033[22;34mRECORY DETAILS\033[0m\n");
    puts("\t\t\t\t\t\t\t\t\t````````````````````````````````\v\v");

    studentPtr = fopen("student.dat", "rb+");
    if (studentPtr == NULL) {
        puts("Error: Could not open the student records");
    }
    else
    {
        char stop_search = 'n';
        puts("\v\v\v\v\t id\t\tfirstName\t\t  lastName   \t\t\t\t D.O.B\t\tfaculty   \t\t     department\t\t\tcourse");
        puts("\t_____________________________________________________________________________________________________________________________________________________________________________________________\v");
             
        while (!feof(studentPtr) && stop_search == 'n')
        {
            STUDENT student2;
            int  result = fread(&student2, sizeof(STUDENT), 1, studentPtr);
            
            if ( strcmp(student2.lname, lname) == 0 && student2.day == day && student2.month == month && student2.year == year && (result != 0) )
            {
                printf(" \t%-15u%-29s%-29s\t%2u/%2u/%-4u\t%-29s%-29s%-29s\n",
                    student2.id, student2.fname, student2.lname,
                    student2.day,student2.month,student2.year,
                    student2.faculty,student2.department,student2.course_title
                    );  
                    puts("\n\t`````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````\n");

            stop_search = 'y'; // stops the search when student found
            
            }
        }
        if (stop_search == 'n') {
            printf("\v\v\t\t\tError: No such student exists");
        }
        puts("\v");

            int choice2;
            puts("\v\v\v\v\v\v\v\t\t\t\t\t\t##########################################################################################");
            printf("\t\t\t\t\t\tEnter 0 to go back to the main menu");
            printf("%s", "\t\t(Enter your choice here)->\t");

            scanf("%u", &choice2);

            if (choice2 == 0)
            {
                // go to the customized view                    
            }
        
    }
    fclose(studentPtr);       
}