#include "pch.h"

using namespace System;
#define _CRT_SECURE_NO_WARNINGS

/*
* Napisati program koji prvo procita koliko redaka ima datoteka, tj.koliko ima studenata zapisanih u
* datoteci.Nakon toga potrebno je dinamicki alocirati prostor za niz struktura
* studenata(ime, prezime, bodovi) i ucitati iz datoteke sve zapise.Na ekran ispisati ime, prezime, apsolutni i relativni broj bodova.
* Napomena: Svaki redak datoteke sadrzi ime i prezime studenta, te broj bodova na kolokviju.
*/

#include <stdio.h>
#include <stdlib.h>

//txt file iz kojega citamo studente
#define studentsFile "studenti.txt"

typedef struct student {
	char ime[25];
	char prezime[25];
	int br_bodova;
}STUDENT;


int ReadLine();
int ReadFromFile(STUDENT*);
int PrintOnScreen(STUDENT*, int);
float RelativeScore(int, int);
int MaxScore(STUDENT*, int);

int main()
{
	int brojStud = 0;
	STUDENT* Student = NULL;


	brojStud = ReadLine();
	if (brojStud > 0)
	{
		printf("broj ucitanih studenata : %d \n", brojStud);

		//alociranje memorije 
		Student = (STUDENT*)malloc(brojStud * sizeof(STUDENT));
		// citanje iz datoteke
		if (ReadFromFile(Student) > 0)
		{
			printf("studenti uspjesno ucitani\n\n");

			// ispis na ekran
			PrintOnScreen(Student, brojStud);
			printf("\n kraj rada !! , hvala na povjerenju \n");
		}
	}
	free(Student);
	return 0;
}

int ReadLine()
{
	/*
	* funkcija ReadLine vraca broj napisanih linija u datoteci
	* sto zapravo predstavlja broj studenata
	**/
	FILE* fp = NULL;
	char buffer[1024] = { 0 };
	int brojac = 0;

	fopen_s(&fp, studentsFile, "r");

	if (fp == NULL)
		printf("Datoteka nije uspjesno otvorena\n");
	else
	{
		while (!feof(fp))
		{	//citamo liniju po liniju sa funkcijom fgets
			fgets(buffer, 1024, fp);
			brojac++;
		}
		fclose(fp);
	}
	return brojac;
}
int ReadFromFile(STUDENT* student)
{
	int br = 0;
	FILE* fp = NULL;
	fp = fopen("studenti.txt", "r");

	if (fp == NULL)
	{
		printf("Error\n");
		return -1;
	}
	else
	{
		while (!feof(fp))
		{	//citanje iz datoteke
			fscanf_s(fp, "%s %s %d", student[br].ime, 25, student[br].prezime, 25, &student[br].br_bodova);
			br++;
		}
		fclose(fp);
		return 1;
	}

}
int PrintOnScreen(STUDENT* student, int br)
{
	float relativeScore = 0;
	int maxBodovi = MaxScore(student, br);
	for (int i = 0; i < br; i++)
	{
		relativeScore = RelativeScore(student[i].br_bodova, maxBodovi);
		printf("%s %s \n broj bodova: %d \n relativni broj: %.2f \n", student[i].ime, student[i].prezime, student[i].br_bodova, relativeScore);
		printf("-------------------------\n");
	}
	return 1;
}
int MaxScore(STUDENT* student, int br)
{
	/*
	*  broj bodova koji je ostvario neki student
	**/
	int max = student[0].br_bodova;
	for (int i = 1; i < br; i++)
	{
		if (student[i].br_bodova > max)
		{
			max = student[i].br_bodova;
		}
	}
	return max;
}
float RelativeScore(int bodovi, int max)
{
	//relativni rezultat
	return (((float)bodovi / max) * 100);
}