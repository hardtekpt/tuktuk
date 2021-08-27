/*
 *  File name: problem.h
 *
 *  Author: Francisco e Joel
 *
 *  date: 2018/11
 *
 *  Description: Header file for problem related fucntions
 *
 */

#ifndef ProblemHeader
#define ProblemHeader

#include "heap.h"
#include "utils.h"

typedef struct vertice
{
	int v;
	int wt;
} vertice;

typedef struct point{
	int x;
	int y;
}point;

typedef struct cell{
	int x;
	int y;
	int wt;
}cell;

typedef struct problem{
	int l;
	int c;
	char obj;
	int nPoints;
	point *points;
	unsigned short **city;
	int v;
}problem;

typedef struct solution{
	int l;
	int c;
	char obj;
	int nPoints;
	int cost;
	int nSteps;
	cell *points;
} solution;

void checkMalloc(void* pointer);
void usage();
int getVectMin(int* vect, int n);
void GRAPHpfs(int s,  int st[], unsigned short wt[], int vd, problem pb);

void freeProblem(problem pb);
problem allocateProblem(problem pb);

void saveSolution(solution sol, FILE* fSol);

int checkIfProblemHasSolution(problem pb);
void getAdjacentPoints(int p, int *points, problem pb, int *n);
void getAdjIndex(problem pb, int v, int *v_adj, vertice* vect);
solution solveProblemVariantA(problem pb);
solution solveProblemVariantB(problem pb);
solution solveProblem(problem pb);
void readFile(FILE* fp, FILE* fSol);
int getVertexFromCoord(point pt, problem pb);
int getWtCoord(int v, problem pb);
int getXCoord(int v, problem pb);
int getYCoord(int v, problem pb);



#endif


