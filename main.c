#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int days_in_month_no_leap[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int days_in_month_leap[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char* months[] = {"", "January", "February", "March", 
"April", "May", "June", "July", "August", "September", 
"October", "November", "December"};

void display(int isLeapYear, int day, int month, int year) {
    if(isLeapYear) {
        displayCalendar(day, month, year, days_in_month_leap, months);
    } else {
        displayCalendar(day, month, year, days_in_month_no_leap, months);
    }
}

void displayInstructions() {
    printf("You can : \n'q' or 'Q' -> 'Quit'.\n");
    printf("'P' or 'p' -> previous page.\n");
    printf("'N' or 'n' -> next page.\n");
    printf("'Q' or 'q' -> quit the program.\n");
    printf("'A' or 'a' -> add a note in the calendar.\n");
    printf("'D' or 'd' -> delete a note in the calendar.\n");
    printf("'S' or 's' -> display the first note in the month.\n");
}

int main() {
    // Get current time
    time_t currentTime = time(NULL);

    // Convert current time to local time
    struct tm* localTime = localtime(&currentTime);

    // Extract day, month, and year from local time
    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1;
    int year = localTime->tm_year + 1900;

    int isLeapYear = isLeap(year);
    enableRawMode();
    char key;
    int state = 0;

    displayInstructions();
    display(isLeapYear, day, month, year);

    while(1) {
        // Get key pressed
        read(STDIN_FILENO, &key, 1);
        // Clear the screen
        //clearScreen();

        switch(key) {
            // S -> show note
            case 'S':
            case 's':
                // TODO
                //displayNote()
                break;
            // N -> next page
            case 'N':
            case 'n':
                // Clear the screen
                system("clear");
                displayInstructions();
                month++;
                if(month >= 12) {
                    year++;
                    month = 1;
                    isLeapYear = isLeap(year);
                }
                display(isLeapYear, day, month, year);
                break;
            // P -> previous page
            case 'P':
            case 'p':
                // Clear the screen
                system("clear");
                displayInstructions();
                month--;
                if(month < 1) {
                    month = 12;
                    year--;
                    isLeapYear = isLeap(year);
                }
                display(isLeapYear, day, month, year);
                // Draw previous
                break;
            // Q -> quit the program
            case 'Q':
            case 'q':
                state = 1;
                break;
            // A -> add a note
            case 'A':
            case 'a':
                // TODO
                //setNote();
                break;
            case 'D':
            case 'd':
                // TODO
                //deleteNote()
                break;
            default:
                printf("Cannot use this key.\n");
        }
        if(state) {
            break;
        }
    }

    return 0;
}