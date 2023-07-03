#pragma once
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void enableRawMode();
void colorTerminal(int state);
void displayCalendar(int day, int month, int year, int days[], char* months[]);
int isLeap(int);
void setNote();