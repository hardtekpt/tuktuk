/*
 *  File name: heap.h
 *
 *  Author: Francisco e Joel
 *
 *  date: 2018/11
 *
 *  Description: Header file for graph related fucntions
 *
 */


#ifndef HeapHeader
#define HeapHeader


#include "problem.h"
#include "utils.h"

typedef enum {FALSE,TRUE} BOOL;

typedef struct vertice vertice;

typedef struct point point;

typedef struct problem problem;

void GRAPHpfs(int s,  int st[], unsigned short wt[], int vd, problem pb);

/* inicializa fila com prioridade com número máximo de items */
void PQinit(unsigned Size); 

/* insere item */
void PQinsert(int I); 

/* testa fila vazia */
BOOL PQempty(); 

/* elimina item de maior prioridade */
int PQdelmax(); 

void FixUp(unsigned int Heap[], int Idx);

void FixDown(unsigned int Heap[], int Idx, int N);

void PQdec(int s);

void cleanUp(vertice* vect);

int getXCoord(int v, problem pb);
int getYCoord(int v, problem pb);

#endif
