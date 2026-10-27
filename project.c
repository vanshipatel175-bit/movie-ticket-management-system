#include <stdio.h>
#include <string.h>

#define MAX 50

// Movie structure
struct Movie
{
    int id;
    char name[30];
    char time[20];
    int price;
    int seats;
};

// Booking structure - Stack
struct Booking
{
    int bookingID;
    char customer[30];
    int movieID;
    int noOfSeats;
    int seatNo[10];
    int total;
};

// Movies - Array
struct Movie movies[3] =
{
    {1, "Avengers", "10:00 AM", 200, 10},
    {2, "Pushpa 2", "02:00 PM", 180, 10},
    {3, "Stree 2", "06:00 PM", 150, 10}
};

// Stack
struct Booking stack[MAX];
int top = -1;

// Queue
char queue[MAX][30];
int front = -1, rear = -1;

int nextBookingID = 101;


// Display movies
void displayMovies()
{
    int i;

    printf("\n------ MOVIES ------\n");

    for(i = 0; i < 3; i++)
    {
        printf("%d. %s | Time: %s | Price: Rs.%d | Seats: %d\n",
               movies[i].id,
               movies[i].name,
               movies[i].time,
               movies[i].price,
               movies[i].seats);
    }
}


// Book ticket
void bookTicket()
{
    int movie, n, i;
    char name[30];

    

    printf("\nEnter Movie ID: ");
    scanf("%d", &movie);

    if(movie < 1 || movie > 3)
    {
        printf("Invalid Movie ID!\n");
        return;
    }

    printf("Enter Customer Name: ");
    scanf("%s", name);

    printf("Enter Number of Seats: ");
    scanf("%d", &n);

    if(n <= 0)
    {
        printf("Invalid number of seats!\n");
        return;
    }

    if(n > movies[movie - 1].seats)
    {
        printf("\nNot enough seats available.\n");

        // Add to queue
        if(rear == MAX - 1)
        {
            printf("Waiting queue is full.\n");
        }
        else
        {
            if(front == -1)
                front = 0;

            rear++;

            strcpy(queue[rear], name);

            printf("Customer added to waiting queue.\n");
        }

        return;
    }

    // Push into stack
    top++;

    stack[top].bookingID = nextBookingID++;

    strcpy(stack[top].customer, name);

    stack[top].movieID = movie;

    stack[top].noOfSeats = n;

    // Assign seats
    for(i = 0; i < n; i++)
    {
        stack[top].seatNo[i] =
            10 - movies[movie - 1].seats + i + 1;
    }

    // Reduce seats
    movies[movie - 1].seats -= n;

    // Calculate total
    stack[top].total =
        n * movies[movie - 1].price;


    printf("\n===== TICKET BOOKED =====\n");

    printf("Booking ID : %d\n", stack[top].bookingID);
    printf("Customer   : %s\n", stack[top].customer);
    printf("Movie      : %s\n", movies[movie - 1].name);
    printf("Time       : %s\n", movies[movie - 1].time);
    printf("Seats      : ");

    for(i = 0; i < n; i++)
    {
        printf("%d ", stack[top].seatNo[i]);
    }

    printf("\nTotal      : Rs.%d\n", stack[top].total);

    printf("=========================\n");
}


// Cancel ticket
void cancelTicket()
{
    int id, i, j;
    int position = -1;
    int movie;

    if(top == -1)
    {
        printf("\nNo bookings available.\n");
        return;
    }

    printf("\nEnter Booking ID: ");
    scanf("%d", &id);

    // Find booking
    for(i = 0; i <= top; i++)
    {
        if(stack[i].bookingID == id)
        {
            position = i;
            break;
        }
    }

    if(position == -1)
    {
        printf("Booking ID not found!\n");
        return;
    }

    movie = stack[position].movieID;

    printf("\n===== TICKET CANCELLED =====\n");

    printf("Booking ID : %d\n", stack[position].bookingID);
    printf("Customer   : %s\n", stack[position].customer);
    printf("Movie      : %s\n", movies[movie - 1].name);
    printf("Seats      : ");

    for(j = 0; j < stack[position].noOfSeats; j++)
    {
        printf("%d ", stack[position].seatNo[j]);
    }

    printf("\nAmount     : Rs.%d\n", stack[position].total);


    // Increase available seats
    movies[movie - 1].seats += stack[position].noOfSeats;


    // Remove booking from stack
    for(i = position; i < top; i++)
    {
        stack[i] = stack[i + 1];
    }

    top--;

    printf("\nTicket cancelled successfully!\n");
    printf("Seats are available again.\n");
}


// Display bookings
void displayBookings()
{
    int i, j;
    int movie;

    if(top == -1)
    {
        printf("\nNo bookings available.\n");
        return;
    }

    printf("\n------ BOOKINGS ------\n");

    for(i = 0; i <= top; i++)
    {
        movie = stack[i].movieID;

        printf("\nBooking ID : %d", stack[i].bookingID);
        printf("\nCustomer   : %s", stack[i].customer);
        printf("\nMovie      : %s", movies[movie - 1].name);
        printf("\nTime       : %s", movies[movie - 1].time);
        printf("\nSeats      : ");

        for(j = 0; j < stack[i].noOfSeats; j++)
        {
            printf("%d ", stack[i].seatNo[j]);
        }

        printf("\nTotal      : Rs.%d\n", stack[i].total);
    }
}


// Display waiting queue
void displayQueue()
{
    int i;

    if(front == -1 || front > rear)
    {
        printf("\nWaiting queue is empty.\n");
        return;
    }

    printf("\n------ WAITING QUEUE ------\n");

    for(i = front; i <= rear; i++)
    {
        printf("%d. %s\n", i - front + 1, queue[i]);
    }
}


// Main function
int main()
{
    int choice;

    do
    {
        printf("\n==============================");
        printf("\n   MOVIE TICKET MANAGEMENT");
        printf("\n==============================");

        printf("\n1. Display Movies");
        printf("\n2. Book Ticket");
        printf("\n3. Cancel Ticket");
        printf("\n4. Display Bookings");
        printf("\n5. Display Waiting Queue");
        printf("\n6. Exit");

        printf("\n\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                displayMovies();
                break;

            case 2:
                bookTicket();
                break;

            case 3:
                cancelTicket();
                break;

            case 4:
                displayBookings();
                break;

            case 5:
                displayQueue();
                break;

            case 6:
                printf("\nThank you!\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while(choice != 6);

    return 0;
}