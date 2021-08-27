/*
 *  File name: utils.c
 *
 *  Author: Francisco e Joel
 *
 *  date: 2018/11
 *
 *  Description: C-Implementation of utility functions
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define DEBUG 1

/*
 *  Função para verificar as alocações de memória
 */
void checkMalloc(void* pointer){
	if(pointer == NULL){
		if(DEBUG==1) printf("Memory allocation error!\n");
		exit(0);
	}
}

/*
 *  Função para verificar o formato do ficheiro introduzido
 */
void usage(){
	if(DEBUG==1) printf("Usage: ./tuktuk <nome>.cities\n");
	exit(0);
}

/*
 *  Função para devolver o valor minimo de um vetor
 */
int getVectMin(int* vect, int n){
	int min = vect[0], i;

	for(i=0; i<n; i++){
		if(vect[i] < min)
			min = vect[i];
	}

	return min;
}















