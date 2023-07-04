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

void displayNote(Notes* notes) {
    Notes* curr = notes;
    
    int day;
    int month;
    int year;

    printf("Day :");
    scanf("%d", &day);

    printf("\nMonth :");
    scanf("%d", &month);

    printf("\nYear :\n");
    scanf("%d", &year);

    while(curr != NULL) {
        if(curr->day == day && curr->month == month && curr->year == year) {
            printf("\033[32m%s\033[0m\n", curr->message);
            return;
        }
        curr = curr->next;
    }
    printf("Note not found.\n");
}

void deleteNote(Notes** notes) {
    Notes* curr = *notes;
    Notes* prev = NULL;

    int day;
    int month;
    int year;

    printf("Day :");
    scanf("%d", &day);

    printf("\nMonth :");
    scanf("%d", &month);

    printf("\nYear :\n");
    scanf("%d", &year);

    while(curr != NULL) {
        if(curr->day == day && curr->month == month && curr->year == year) {
            if(prev == NULL) {
                // First element in the linked list
                *notes = curr->next;
            } else {
                prev->next = curr->next;
            }

            free(curr);
            printf("Note deleted.\n");
            return;
        }

        prev = curr;
        curr = curr->next;
    }
    printf("Cannot remove the note.\n");
}

void setNote(Notes** notes) {
    char message[42];
    int day;
    int month;
    int year;

    printf("Day :");
    scanf("%d", &day);

    printf("\nMonth :");
    scanf("%d", &month);

    printf("\nYear :");
    scanf("%d", &year);

    printf("\nGet your message (42 characters max) :");
    scanf("%s", message);

    Notes* newNode = malloc(sizeof(Notes));
    newNode->day = day;
    newNode->month = month;
    newNode->year = year;
    strcpy(newNode->message, message);
    newNode->next = *notes;
    *notes = newNode;
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

void displayCalendar(Notes* notes, int day, int month, int year, int days[], char* months[])
{
    printf("\n");
    int daycode;
    struct tm timeinfo = {0};
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = 0;

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

    printf("\n\nMon  Tue  Wed  Thu  Fri  Sat Sun\n");

    // Correct the position for the first date
    for (day = 1; day < daycode * 5; day++)
    {
        printf(" ");
    }
    
    // Print all the dates for one month
    for (int dayIdx = 1; dayIdx <= days[month]; dayIdx++)
    {
        if(isNote(notes, dayIdx, month, year)) {
            printf("\033[31m%2d\033[0m", dayIdx);
        } else {
            printf("%2d", dayIdx);
        }
        
        if ((dayIdx + daycode) % 7 > 0 )
            printf("   ");
        else
            printf("\n ");
    }
    printf("\n");
}

void freeNote(Notes* notes) {
    Notes* curr = notes;
    while(curr != NULL) {
        Notes* next = curr->next;
        free(curr);
        curr = next;
    }
}

int isNote(Notes* notes, int day, int month, int year) {
    Notes* curr = notes;
    while(curr != NULL) {
        if(curr->day == day && curr->month == month && curr->year == year) {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}