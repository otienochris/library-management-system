#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define FALSE 0;
#define TRUE 1;


/* this function allows the adnin to specify the available transport details
also it allows the customer to view the transport details  */
void Transport();

/* this function will allow the customers to view and chose a seat during reservation */
void Seat_info();

/* This function will allow the customer to reserve a ticket */
void Reservation();

/* This is a payment interface */
void Payment();

/* This answers the customers question of 'which routes does this company cover?' */
void Route_info();

/* This function assigns duties to the drivers automatically if they are available */
void Scheduling();

/* Entry of drivers' info */
void Drivers_info();

/* This function shows the salary with respect to their ratings ang job groub */
void Salary_info();


/*  */void Job_group();
void Customer_ratings();



int main()
{

    int admin = FALSE; 

    printf("");
    printf("");
    printf("");
    printf("");
    printf("");
    printf("");
    printf("");
    printf("");
    printf("");
    printf("");
    printf("");


    // i for navigation
    int i;
    scanf("%d", &i);

    // choosing what to view
    switch (i) {
        case 1:
            Route_info();
            break;
        case 2:
            Transport();
            break;
        case 3:
            Seat_info();
            break;
        case 4:
            Reservation();
            break;
        case 5:
            Payment();
            break;
        case 6:
            // add a for loop to verify if admin to view
            // if x[i] && y[j]            
            Drivers_info();
            break;
        case 7:
            // add a for loop to verify if admin to view
            // if x[i] && y[j]            
            Salary_info();
            break;
        case 8:
            // add a for loop to verify if admin to view
            // if x[i] && y[j]
            break;
        case 9:
            // add a for loop to verify if admin to view
            // if x[i] && y[j]
            Job_group();
            break;
        case 10:
            exit(1);
            break;
        

    }

    return 0;
}



// this function allows the adnin to specify the available transport details
// also it allows the customer to view the transport details 
void Transport(){

    int transport_id;
    float price;
    char driver[15], from[10], to[10];

    printf("Transport_id: ");
    scanf("%d", &transport_id);
    printf("Driver name : ");
    scanf("%s", &driver);
    printf("From : ");
    scanf("%s", &from);
    printf("To : ");
    scanf("%s", &to);
    printf("Price : ");
    scanf("%f", &price);

}

