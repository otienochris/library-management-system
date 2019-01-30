#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char first_name[15];
    char last_name[15];
    char reg_number[15];
    char email[10];
} stud;

struct book {
    int book_id;
    char book_name[15];
    char book_author[15];
    int copies;
} bk;

// global pointers
FILE *bookPtr, *studentPtr;

void add_book (void);
void add_student(void);

int main()
{

add_book();
// add_student();

}

void add_book (void)
{

    if((bookPtr = fopen("book.tx","a+")) == NULL )
    {
        puts("Erro opening the file");
    }
    else
    {
        while(!feof(stdin))
        {
            puts("Enter book id : ");
            scanf("%d", &bk.book_id);
           /*  puts("Enter book title : ");
            scanf("%s", &bk.book_name);
            puts("Enter book author : ");
            scanf("%s", &bk.book_author);*/
            puts("Enter book copies : "); 
            scanf("%d", &bk.copies);
            fprintf(bookPtr, "\r\n");
            fprintf(bookPtr, "id\tcopies" );
            fprintf(bookPtr, "%d\t%d\t", bk.book_id,bk.copies );
        }

        fclose(bookPtr);
    }


}
  