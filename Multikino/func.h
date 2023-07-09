#pragma once

int exist(char *fileName, int create, int seats, int rows);

void drawHall(char nameF[30], int projectionHall[10][20], int rows, int seats);

int randomNumberOfReservation();

void addReservation(char* reservation);

int letterToNumber(char letter);

void time(int today[3], int tommorow[3], int afterTommorow[3]);

int numberCheck(char text[50], int min, int max); //char *text

int letterCheck(char text[50], int min, int max);
