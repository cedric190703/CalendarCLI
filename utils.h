#pragma once
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

// Implement a linked list for storing all the notes for the calendar
typedef struct Note {
    int day;
    int month;
    int year;
    char* message;
} Note;

typedef struct Notes {
    Note *head;
    Note *tail;
} Notes;

void enableRawMode();
void colorTerminal(int state);
void displayCalendar(int day, int month, int year, int days[], char* months[]);
int isLeap(int);
void displayNote(Notes* notes, int day, int month, int year);
void deleteNote(Notes* notes, int day, int month, int year);
void setNote(Notes* notes, int day, int month, int year);