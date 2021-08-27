/*
 *  File name: utils.c
 *
 *  Author: Francisco e Joel
 *
 *  date: 2018/11
 *
 *  Description: C-Implementation of file functions
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

#define DEBUG				 0


/*
 *  Função para escrever a solução no ficheiro de saida 
 */
void saveSolution(solution sol, FILE* fSol){
	int i;
	fprintf(fSol,"%d %d %c %d %d %d\n", sol.l, sol.c, sol.obj, sol.nPoints, sol.cost, sol.nSteps);
	for(i=0; i<sol.nSteps; i++){
		fprintf(fSol, "%d %d %d\n", sol.points[i].x, sol.points[i].y, sol.points[i].wt);
	}
	fprintf(fSol,"\n");
}

/*
 *  Função para abrir ficheiros para ler ou escrever dependendo da extension
 */
FILE* openFile(char* fileName, char mode, char* extension){
	FILE *f;
	int i = 0;
	int len = strlen(fileName) - 1;
	char *solName;


	if (mode == 'w') {

		solName =  malloc((len+1) * sizeof(char));

		while (len != 0)
		{
			if ( fileName[len] == '.')
				break;
			len--;
		}

		for (i = 0; i < len; i++){
			solName[i] = fileName[i];
		}

		solName[len] = '\0';

        strcat(solName, extension);
		f = fopen(solName, "w");
		free(solName);
	}
	else {
		if(strstr(fileName, extension) == NULL){
	    	if(DEBUG==1)printf("Wrong file format!\n");
	    	usage();
	    	exit(0);
		}
		f = fopen(fileName, "r");
		if (f == (FILE*) NULL) {
	    	if(DEBUG==1)printf("Could not open filename %s.  Exiting...\n", fileName);
	    	exit(0);
	  	}
	 }

  	return f;
}





