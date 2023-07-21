#pragma once
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// Implement a linked list for storing all the notes for the calendar
typedef struct Notes {
    int day;
    int month;
    int year;
    char message[42];
    struct Notes* next;
} Notes;

void enableRawMode();
void colorTerminal(int state);
void displayCalendar(Notes* notes, int day, int month, int year, int days[], char* months[]);
int isLeap(int);
void displayNote(Notes* notes);
void deleteNote(Notes** notes);
void setNote(Notes** notes);
void freeNote(Notes* notes);
int isNote(Notes* notes, int day, int month, int year);