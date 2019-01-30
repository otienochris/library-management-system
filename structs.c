
// structs

// details of the book
typedef struct
{
    unsigned int id, copies;
    char title[30], author[30];
} BOOK;

// date values
typedef struct
{
    unsigned int day, month, year ;
} DATE;

// semester info
typedef struct
{
    unsigned int year, sem;
} SEM_INFO;

// details of the student
typedef struct
{
    // COURSE course;
    // DATE dob;
    unsigned int day, month, year ;
    char id[30], fname[30], lname[30];
    char faculty[30], department[30], course_title[30];
} STUDENT;

// course information
typedef struct MyStruct
{
    char faculty[30], department[30], course_title[30];
} COURSE;
