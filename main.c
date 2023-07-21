#include <stdio.h>
#include <stdlib.h>
#include "utils/utils.h"

int days_in_month_no_leap[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int days_in_month_leap[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char* months[] = {"", "January", "February", "March", 
"April", "May", "June", "July", "August", "September", 
"October", "November", "December"};

void display(Notes* nodes, int isLeapYear, int day, int month, int year) {
    if(isLeapYear) {
        displayCalendar(nodes, day, month, year, days_in_month_leap, months);
    } else {
        displayCalendar(nodes, day, month, year, days_in_month_no_leap, months);
    }
}

void displayInstructions() {
    printf("You can : \n'q' or 'Q' -> 'Quit'.\n");
    printf("'P' or 'p' -> previous page.\n");
    printf("'N' or 'n' -> next page.\n");
    printf("'Q' or 'q' -> quit the program.\n");
    printf("'A' or 'a' -> add a note in the calendar.\n");
    printf("'D' or 'd' -> delete a note in the calendar.\n");
    printf("'S' or 's' -> display note.\n");
    printf("'G' or 'g' -> refresh the calendar.\n");
}

void displayContent() {
    // Clear the screen
    system("clear");
    displayInstructions();
}

void displaySeparator() {
    printf("\n");
    for(int i = 0; i < 26; i++) {
        printf("-");
    }
    printf("\n");
}

int main() {
    // Get current time
    time_t currentTime = time(NULL);
    Notes* notes = NULL;

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
    display(notes, isLeapYear, day, month, year);

    while(1) {
        // Get key pressed
        read(STDIN_FILENO, &key, 1);

        switch(key) {
            // To refresh the calendar
            case 'G':
            case 'g':
                displayContent();
                display(notes, isLeapYear, day, month, year);
                break;
            // S -> show note
            case 'S':
            case 's':
                displayContent();
                display(notes, isLeapYear, day, month, year);
                displaySeparator();
                printf("Display a note.\n");
                printf("\n");
                displayNote(notes);
                displaySeparator();
                break;
            // N -> next page
            case 'N':
            case 'n':
                displayContent();
                month++;
                if(month >= 12) {
                    year++;
                    month = 1;
                    isLeapYear = isLeap(year);
                }
                display(notes, isLeapYear, day, month, year);
                break;
            // P -> previous page
            case 'P':
            case 'p':
                displayContent();
                month--;
                if(month < 1) {
                    month = 12;
                    year--;
                    isLeapYear = isLeap(year);
                }
                display(notes, isLeapYear, day, month, year);
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
                displayContent();
                display(notes, isLeapYear, day, month, year);
                displaySeparator();
                printf("Add a note.\n");
                printf("\n");
                setNote(&notes);
                displaySeparator();
                break;
            case 'D':
            case 'd':
                displayContent();
                display(notes, isLeapYear, day, month, year);
                displaySeparator();
                printf("Remove a note.\n");
                printf("\n");
                deleteNote(&notes);
                displaySeparator();
                break;
            default:
                printf("Cannot use this key.\n");
        }
        if(state) {
            break;
        }
    }

    free(notes);
    return 0;
}