#include "utils.h"

// Function to enable raw terminal input mode
void enableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

// Function to disable raw terminal input mode
void disableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

void displayNote(Notes* notes, int day, int month, int year) {
    // Search for the note in the notes
}

void deleteNote(Notes* notes, int day, int month, int year) {
    // Delete the note in the notes
}

void setNote(Notes* notes, int day, int month, int year) {
    // Add a note in the notes
}

int isLeap(int year) {
    if(year%4 == 0) {
        if(year%100 == 0) {
            if(year%400 == 0) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 1;
        }
    }
    return 0;
}

void displayCalendar(int day, int month, int year, int days[], char* months[])
{
    printf("\n");
    int daycode;
    struct tm timeinfo = {0};
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = 1;
    
    mktime(&timeinfo);
    
    daycode = timeinfo.tm_wday;

    for(int i = 0; i < 38; i++) {
        printf("-");
    }
    printf("\n");
    printf("%d, %s , %d", day, months[month], year);
    printf("\n");

    for(int i = 0; i < 38; i++) {
        printf("-");
    }

    printf("\n\nMon  Tue  Wed  Thu  Fri  Sat Sun\n" );

    // Correct the position for the first date
    for ( day = 1; day <= daycode * 5; day++ )
    {
        printf(" ");
    }
    
    // Print all the dates for one month
    for (int dayIdx = 1; dayIdx <= days[month]; dayIdx++ )
    {
        printf("%2d", dayIdx);
        
        // Is day before Sat? Else start next line Sun.
        if ((dayIdx + daycode) % 7 > 0 )
            printf("   ");
        else
            printf("\n ");
    }
    printf("\n");
}