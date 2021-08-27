/*
 *  File name: heap.c
 *
 *  Author: Francisco e Joel
 *
 *  date: 2018/11
 *
 *  Description: C-Implementation of heap related functions
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "heap.h"

#define DEBUG				 0
#define MAXRPOINTS           8

//#define P (wt[v] + vect[t].wt)
#define lessPri(A, B) (key[A] > key[B])
#define exch(A, B) {int t = A; A = B; B = t; }

static unsigned int *queue;
static int pqfree; /* primeira posição livre */  /* número de elementos existentes no acervo */
static int hsize;  /* tamanho da tabela */
static int maxWT = 1000;
static unsigned short *key;
static unsigned int *index;

void printQueue(){
	int i;
	for(i=0; i<pqfree; i++){
		printf("%d - ", queue[i]);
	}
	printf("\n");
}

/*
 *  Função onde se desenvolve o algoritmo
 */
void GRAPHpfs(int s,  int st[], unsigned short wt[], int vd, problem pb) {
	int v, w, t;
	vertice *vect;
	key = wt;
    vect = (vertice *) malloc(MAXRPOINTS * sizeof(vertice));
    checkMalloc(vect);

	int n_adj = 0;     //para contagem do nº de vertices adjacentes

	PQinit((pb.l * pb.c) + 1);
	for (v = 0; v < (pb.l * pb.c); v++) {
		st[v] = -1;
		wt[v] = maxWT;
		if(pb.city[getXCoord(v, pb)][getYCoord(v, pb)] != 0)
			PQinsert(v);	
	}

	wt[s] = 0;
	PQdec(s);
		

	while (!PQempty()){
		if (wt[v = PQdelmax()] != maxWT){
			
			if(v == vd){
				cleanUp(vect);
				return;
			}

			getAdjIndex(pb, v, &n_adj, vect); // vetor de adjacencias

			for (t = 0; t < n_adj; t++)
				if (wt[w = vect[t].v] > wt[v] + vect[t].wt) {
					wt[w] = wt[v] + vect[t].wt;	
					PQdec(w);
					st[w] = v;	
				}
		}
	}
	cleanUp(vect);
}

BOOL PQempty() {
	return pqfree == 0 ? TRUE : FALSE;
}

void PQdec(int s){
	FixUp(queue, index[s]);
}

void PQinit(unsigned Size) {
	queue = (unsigned int *)malloc(Size*sizeof(unsigned int));
	hsize = Size; pqfree = 0; 

	index = (unsigned int *) calloc(Size, sizeof(unsigned int));
}

void PQinsert(int I) {
	/* insere novo elemento no fim e restabelece ordenação com FixUp */
	queue[pqfree] = I;
	index[I] = pqfree;
	FixUp(queue, pqfree);
	pqfree++;
}

int PQdelmax() {
	/* troca maior elemento com último da tabela e reordena com FixDown */
	int max = queue[0];
	pqfree--;
	exch(queue[0], queue[pqfree]);
	exch(index[queue[0]], index[queue[pqfree]]);
	FixDown(queue, 0, pqfree);
	/* ultimo elemento não considerado na reordenação */
	return max;
}

void FixUp(unsigned int Heap[], int Idx) {
	while (Idx > 0 && lessPri(Heap[(Idx-1)/2], Heap[Idx])) {
		exch(Heap[Idx], Heap[(Idx-1)/2]);
		exch(index[Heap[Idx]], index[Heap[(Idx-1)/2]]);
		Idx = (Idx-1)/2;
	}
}


void FixDown(unsigned int Heap[], int Idx, int N) {
	int Child; /* índice de um nó descendente */
	while(2*Idx < N-1) { /* enquanto não chegar às folhas */
		Child = 2*Idx+1;
		/* Selecciona o maior descendente. */
		/* Nota: se índice Child é N-1, então só há um descendente */
		if (Child < (N-1) && lessPri(Heap[Child], Heap[Child+1])) 
			Child++;
		if (!lessPri(Heap[Idx], Heap[Child]))
			break;

		exch(Heap[Idx], Heap[Child]);
		exch(index[Heap[Idx]], index[Heap[Child]]);
		
		/* continua a descer a árvore */
		Idx = Child;
	}
}

void cleanUp(vertice* vect){
	free(index);
	free(queue);
	free(vect);
}





