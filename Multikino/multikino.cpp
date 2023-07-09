#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>																	//vypnutí save warning proojekt - vlastnosti - c/c++ - postprogram _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <tchar.h>
#include <SDKDDKVer.h>


#define seats 20																	//makro - definujme kolik budeme mít sedaček a kolik řad
#define rows 10

int projectionHall[rows][seats];
char *films[20] = { (char*)"Music", (char*)"Fatal", (char*)"Hlasy",  (char*)"Hobit", (char*)"Kolja" };
char nameF[30] = "backup.txt";

struct visitors																		//deklarování struktury a zárovrń naplnění
{
	char* film;
	char date[50];
	char* time;
	char placeLetter;																// písmeno řady sedadel
	int placeNumber;																// číslo řady sedadel
	int number;																		//rok narozeni zakaznika
	int token;																		// unikátní kód
}visitor;

int date[3], today[3], tomorrow[3], afterTomorrow[3];								//deklarování polí dnů a data


int main(int argc, char *argv[])
{

	int date[3], today[3], tomorrow[3], afterTomorrow[3];

	today[0] = 9;
	today[1] = 12;
	today[2] = 2020;
	
	tomorrow[0] = 10;
	tomorrow[1] = 12;
	tomorrow[2] = 2020;


	afterTomorrow[0] = 11;
	afterTomorrow[1] = 12;
	afterTomorrow[2] = 2020;



	int end = 0;
	int helpVariable = 99;
	char helpArray[100];

	int line = 0;
	char input[50];
	
	printf("|===============================================================================|\n");			//uvitaci obrazovka
	printf("|----------------------- Rezervacni system kina PEKAMI -------------------------| \n");
	printf("|===============================================================================|\n|                                                                               |");

	while (end == 0)
	{
		printf("\n|\tVyberte si film z nabidky filmu:                                        |\n");													//cyklus kde se zobrazí filmy (pomocí čisla si vybíráme film)
		printf("|-------------------------------------------------------------------------------|\n");
		for(int i = 0; i <= 6; i++)
		{
			if (films[i] == 0)
			{
				break;
			}
			printf("|\t%d pro zvolení filmu: %s                                     \t\t|\n", i, films[i]);
		}
		printf("|_______________________________________________________________________________|\n");
		helpVariable = numberCheck((char*)"|\tVyberte cislo filmu z nabidky:                                          |\n|\t\t\t\t Vybrali jste:\t", 0, 5);			//pokračování cyklu - pro zadávání čisala pro zadání film
		visitor.film = films[helpVariable];

		printf("|_______________________________________________________________________________|\n");
		printf("|                                                                               |\n");
		printf("|\tVyberte si datum promitani vybraneho filmu %s\t\t\t|\n", films[helpVariable]);			//pokračování cyklu - pro zadávání čisala pro zvolení datum		time(today, tomorrow, afterTomorrow);
		printf("|-------------------------------------------------------------------------------|\n");

		visitor.time = (char*)"18:00";
		printf("|\t0 pro vyber %d.%d.%d v promitacim sale %d v case %s\t\t\t|\n", today[0], today[1], today[2], helpVariable, visitor.time);					//vyběr v jaký datum a čas 
		printf("|\t1 pro vyber %d.%d.%d v promitacim sale %d v case %s\t\t\t|\n", tomorrow[0], tomorrow[1], tomorrow[2], helpVariable, visitor.time);
		printf("|\t2 pro vyber %d.%d.%d v promitacim sale %d v case %s\t\t\t|\n", afterTomorrow[0], afterTomorrow[1], afterTomorrow[2], helpVariable, visitor.time);

		printf("|_______________________________________________________________________________|\n");
		printf("|                                                                               |\n");
		helpVariable = numberCheck((char*)"|\tVyberte datum prosim:\t\t\t\t\t\t\t|\n|\t\t\t\t Vybrali jste:\t", 0, 2);
		printf("|_______________________________________________________________________________|\n");

		switch(helpVariable)										//přepínač (podle čísla se vybere určitá třída (dnes, zítra, pozítří))		
		{
			case 0:
				date[0] = today[0];
				date[1] = today[1];
				date[2] = today[2];
				break;

			case 1:
				date[0] = tomorrow[0];
				date[1] = tomorrow[1];
				date[2] = tomorrow[2];
				break;

			case 2:
				date[0] = afterTomorrow[0];
				date[1] = afterTomorrow[1];
				date[2] = afterTomorrow[2];
				break;

			default:
				break;
		}

		sprintf_s(visitor.date, sizeof(visitor.date), "%d.%d.%d", date[0], date[1], date[2]);															//zapíše datum do paměti funkce
		sprintf_s(nameF, sizeof(nameF), "%s-%s", visitor.date, visitor.film);

		drawHall(nameF, projectionHall, rows, seats);																									//volání funkce pro vykreslení promítacího sálu

		while(1 == 1)																																	//cyklus pro zadávání písmena a čísla (odkaz na funkce které kontrolují zda je zapsané správě) 
		{
			//======================================================================================  ZKONTROLOVANI JESTLI SE ZADAVA SPRAVE PISMENO  ========================
			visitor.placeLetter = letterCheck((char*)"|\t\t\t\t\t\t\t\t\t\t|\n|\tZADEJTE PISMENO MISTA\t\t\t\t\t\t\t|\n|\t\t\t\t Zadali jste:\t", 0 , 1);
			getchar();																	  																//vyprázdnění buffru klávesnice

			//======================================================================================  ZKONTROLOVANI JESTLI SE ZADAVA SPRAVE CISLO ===========================
			printf("|-------------------------------------------------------------------------------|\n");
			visitor.placeNumber = numberCheck((char*)"|\t\t\t\t\t\t\t\t\t\t|\n|\tZADEJTE CISLO MISTA\t\t\t\t\t\t\t|\n|\t\t\t\t Zadali jste:\t", 0, 9);

			//======================================================================================  ZJIŠTĚNÍ JESTLI JE JIŽ OBSAZENÉ MÍSTO  ================================
			if (projectionHall[visitor.placeNumber] [helpVariable] == 0)
			{
				printf("|_______________________________________________________________________________|\n");
				helpVariable = numberCheck((char*)"|\tToto sedadlo je jiz  obsazene, prosim vyberte jine nebo akci zruste!\t|\n|\t\tZRUSIT AKCI = 0   OPAKOVAT AKCI = 1\t\t\t\t|\n|\t\t\t\t Vybrali jste:\t", 0, 2);
				if (helpVariable != 1)
				{
					printf("|\t\t\t\t\t\t\t\t\t\t|\n");
					printf("|===============================================================================|\n");
					printf("|-------------------------------- NASHLEDANOU ----------------------------------|\n");
					printf("|===============================================================================|\n\n");
					exit(0);
				}
			}
			else break;
		}
		printf("|-------------------------------------------------------------------------------|\n");
		visitor.number = numberCheck((char*)"|\tZadejte vas rok narozeni: \t\t\t\t\t\t|\n|\t\t\t\t Zadali jste:\t", 1000, 3000);																//kontroluje se zda je zadané správné číslo a ukládá do visitor.number
		visitor.token = randomNumberOfReservation();																									//visitor.token - volá funkci náhodné identifikační číslo

		printf("|_______________________________________________________________________________|\n|\t\t\t\t\t\t\t\t\t\t|\n");
		printf("|\tSedadlo %c%d uspesne zarezrvovano.\t\t\t\t\t|\n", visitor.placeLetter, visitor.placeNumber);			//vypíše větu a do ní proměnné
		printf("|\tZapiste si Vas unikatni kod rezervace : %04d / %d\t\t\t|\n", visitor.number, visitor.token);
		printf("|\tpro promitani %s ", nameF);
		printf("%d\t\t\t\t\t|\n", visitor.time);
		// printf("\nv case %s", visitor.time);
		printf("|\tDekujeme za rezervaci!\t\t\t\t\t\t\t|\n");
		printf("|_______________________________________________________________________________|\n");

		sprintf_s(helpArray, sizeof(helpArray), "sedadlo: %c%d unikatni kod: %04d/%d, promitani: %s", visitor.placeLetter, visitor.placeNumber, visitor.number, visitor.token, nameF);			//zapisuje do paměti helpArray
		addReservation(helpArray);


		//========================================================================================  NACTENI HODNOT  ===========================================================
		FILE* pToFile;
		fopen_s(&pToFile, nameF, "r");																													//podla filmu a datumu
		while (fgets(input, 50, pToFile)) {
			for (int i = 0; i < seats; i++) {
				projectionHall[line][i] = input[i] - '0';																								//char na int
			}
			line++;
		}
		fclose(pToFile);

		helpVariable = letterToNumber(visitor.placeLetter);																								//zmen hodnotu z pismena na cislo
		
		//printf("%d\n", helpVariable);
		//printf("%d\n", visitor.placeNumber);

		visitor.placeLetter = tolower(visitor.placeLetter);
		visitor.placeLetter = visitor.placeLetter - 97;							

		projectionHall[visitor.placeNumber][visitor.placeLetter] = 0;				// tolower() 																			//obsadene
		visitor.placeLetter = visitor.placeLetter - 97;

		//projectionHall[visitor.placeLetter][visitor.placeNumber] = 0;				// tolower() 																			//obsadene

		//==========================================================================================  ZAPIS HODNOT  =============================================================
		fopen_s(&pToFile, nameF, "w+");																													// nameF => je nazev souboru
		for (int j = 0; j < rows; j++)
		{
			for (int i = 0; i < seats; i++)
			{
				fprintf(pToFile, "%d", projectionHall[j][i]);
			}
			fprintf(pToFile, "\n");
		}
		fclose(pToFile);
		//==========================================================================================  UKONCENI PROGRAMU  =============================================================
		helpVariable = numberCheck((char*)"|\t\t\t\t\t\t\t\t\t\t|\n|\tPREJETE PRIDAT DALSI REZRVACI? ANO=1, NE=0 \t\t\t\t|\n|\t\t\t\t Vybrali jste:\t", 0, 1);
		printf("|\t\t\t\t\t\t\t\t\t\t|\n");
		printf("|===============================================================================|\n");

		if (helpVariable == 1) 
		{ 
			end = 0; 
		}
		else 
		{ 
			//printf("|\t\t\t\t\t\t\t\t\t\t|\n");
			//printf("|===============================================================================|\n");
			printf("|-------------------------------- NASHLEDANOU ----------------------------------|\n"); 
			printf("|===============================================================================|\n\n");
			exit(0); 
		}
	}

	return 0;
}
