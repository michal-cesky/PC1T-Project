#include <stdio.h>													//pøidání knihoven a odkaz na heather soubor
#include <stdlib.h>
#include <time.h>
#include <tchar.h>
#include <SDKDDKVer.h>
#include <string.h>
#include "func.h"
#pragma warning(disable:4996)

int exist(char *fileName, int create, int seats, int rows)			//funkce zajišue zda je vytvoøenı soubor jestli ne tak ho vytvoøí
{
	FILE *file;
	if (file = fopen(fileName, "r"))								//kontroluje zda je vytvoreny soubor
	{		
		fclose(file);
		return 1;
	}

	if (create == 1)
	{
		file = fopen(fileName, "wb");								//otevre soubor a vytvari ho
		for (int j=0; j < seats; j++)
		{
			for (int i = 0; i < rows; i++)
			{
				fprintf(file, "%c", '1');
			}
			fprintf(file, "\n");
		}
		fclose(file);
	}

	return 0;
}

void drawHall(char nameF[30], int projectionHall[10][20], int rows, int seats)						//deklarace funkce drawHall (zobrazení a obsazenost kinosálu)
{
	int line = 0;
	char in[50];
	exist(nameF, 1, rows, seats);									//voláni funkce exist

	FILE* hToFile = fopen(nameF, "r");

	while (fgets(in, 50, hToFile))								//pøevod char na int
	{
		for (int i = 0; i < seats; i++)
		{
			projectionHall[line][i] = in[i] - '0';
		}
		line++;
	}
	fclose(hToFile);

	printf("|\t\t\t\t\t\t\t\t\t\t|\n|\tObsazeni salu:\t\t\t\t\t\t\t\t|\n|-------------------------------------------------------------------------------|\n|\t\t\t\t\t\t\t\t\t\t|\n");

	for (int j = 0; j < rows; j++)								//cyklus pro obsazenost sálu
	{
		if (j == 0)
		{
			printf("|    -----------------PLATNO------------------\t\t\t\t\t|\n|    |A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|\t\t\t\t\t|\n\n %02d",j);
		}
		printf("  ");
		for (int i = 0; i < seats; i++)							
		{
			if (projectionHall[j][i] == 0)						//grafické zobrazení zda je místo obsazeno
			{
				printf("|#");									//obsazeno
			}
			else
			{
				printf("|_");									//volno
			}
		}

		if ( j != rows - 1)
		{
			printf("|\n %02d", j + 1);
		}
	}
	printf("|\n|\t\t\t\t\t\t\t\t\t\t|\n|-------------------------------------------------------------------------------|\n");
	printf("|\tVolna sedadla jsou oznacena |_|. \t\t\t\t\t|\n");
	printf("|\tObsazena sedadla jsou oznacena |#|. \t\t\t\t\t|\n");
	printf("|_______________________________________________________________________________|\n");
}

int randomNumberOfReservation()								//deklarace funkce která generuje náhodné èíslo pro rezervaci
{
	srand(time(NULL));
	int r = rand() % 888888;
	r = r + 111111;
	return r;												//návratová hodnota je náhodné èíslo
}

void addReservation(char* reservation)						//deklarace funkce pro rezervaci - pøidává rezervace do textového souboru
{
	FILE *fh = fopen("reservations.txt", "a+");

	fprintf(fh, "%s\n", reservation);
	fclose(fh);
}

int letterToNumber(char letter)								//deklarace funkce písmeno na èíslo
{
	char alphabet[40] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t',					//deklarace a naplnìní pole pro abecedu
						  'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T' };
	int number;

	for (int i = 0; i <= 40; i++)
	{
		if (letter == alphabet[i])
		{
			if (i > 19)
			{
				i = i - 20;
			}
			return i;								//navratová hodnota bude vdy malé písmeno
		}
		number = i;
	}
	return number;							
}

void time(int today[3], int tomorrow[3], int afterTomorrow[3])						//deklarace funkce pro dny kdy se bude promítat danı film
{
	//int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };	//pole pro maximální poèet dnù v mìsíci

	
	//time_t now = time(NULL);														//aktuální datum
	//struct tm* t = localtime(&now);

	today[0] = 9;
	today[1] = 12;
	today[2] = 2020;
	
	tomorrow[0] = 10;
	tomorrow[1] = 12;
	tomorrow[2] = 2020;


	afterTomorrow[0] = 11;
	afterTomorrow[1] = 12;
	afterTomorrow[2] = 2020;

	//today[0] = t->tm_mday;															//pro denšní den
	//today[1] = t->tm_mon + 1;
	//today[2] = t->tm_year + 1900;


	/*if(today[0]+1<=monthDays[today[1]-1])											//pro zítøek
	{
		tomorrow[0] = today[0]+1;
		tomorrow[1] = today[1];
		tomorrow[2] = today[2];
	}
	else
	{
		if (today[1] == 12)
		{
			tomorrow[0] = 1;
			tomorrow[1] = 1;
			tomorrow[2] = today[2] + 1;
		}
		else
		{
			tomorrow[0] = 1;
			tomorrow[1] = today[1] + 1;
			tomorrow[2] = today[2];
		}
	}

	if(today[0]+2<=monthDays[today[1]-1]){											//pro pozítøek
		afterTomorrow[0]=today[0]+2;
		afterTomorrow[1]=today[1];
		afterTomorrow[2]=today[2];	
	}
	else{
		if(today[1]==12){
			afterTomorrow[0]=((today[0]+2)-monthDays[today[1]-1]);
			afterTomorrow[1]=1;
			afterTomorrow[2]=today[2]+1;
		}
		else{
			afterTomorrow[0]=((today[0]+2)-monthDays[today[1]-1]);
			afterTomorrow[1]=today[1]+1;
			afterTomorrow[2]=today[2];
		}
	}*/
}

int numberCheck(char text[50], int min, int max)								//deklarace funkce pro kontrolu zda bylo zadáno správné èíslo
{
	int out = 0;
	char *p, s[100];															//deklarace lokálních promìnıch
	int n;

	printf("%s", text);

	while(fgets(s, sizeof(s), stdin))
	{
		n = strtol(s, &p, 10);
		out = n;
		if (((p == s || *p != '\n') || (n < min || n > max)))					//podmínka zda je èíslo v daném rozsahu
		{
			printf("|_______________________________________________________________________________|\n");
			printf("|\tCislo musi byt v rozmezi %d-%d, prosim zadejte cislo znovu!\t\t|\n",min,max);
		}
		else
		{
			break;
		}
	}
	return out;
}

int letterCheck(char text[50], int min, int max)								//deklarace funkce pro kontrolu zda bylo zadáno správné písmeno
{
	char alphabet[40]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t',
					   'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T'};
	char variable;

	printf("%s", text);

	scanf_s("%c", &variable, max);

	for (int i = 0; i < 40; i++)												//cyklus pokud bude zapsane pismeno
	{
		if (variable == alphabet[i])											//pokud je zadano pismeno tak bude návratová hodnota toté písmeno
		{
			return variable;
		}
	}
	getchar();
	printf("|_______________________________________________________________________________|\n");
	printf("|          Zadali jste spatne pismeno, prosime zadejte pismeno znovu!           |\n");
	letterCheck(text, min, max);

	return 0;
}
