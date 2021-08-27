/*
 *  File name: main.c
 *
 *  Author: Francisco e Joel
 *
 *  date: 2018/11
 *
 *  Description: Main
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "problem.h"
#include "file.h"

#define DEBUG				 0

#define ENTRYFILEEXTENSION   ".cities"
#define EXITFILEEXTENSION    ".walks"

FILE* openFile(char* fileName, char mode, char* extension);
void readFile(FILE* fp, FILE* fSol);

int main(int argc, char *argv[])
{
	FILE *fp, *fSol;

	if(argc != 2)
		usage();
	/*Abertura dos ficheiros*/
	fp = openFile(argv[1], 'r', ENTRYFILEEXTENSION);
	fSol = openFile(argv[1], 'w', EXITFILEEXTENSION);

	/*Leitura do ficheiro de entrada*/
	readFile(fp, fSol);

	/*Fecho dos ficheiros*/
	fclose(fp);
	fclose(fSol);

	if(DEBUG==1)printf("\nProgram terminated with success\n");
	return 0;
}