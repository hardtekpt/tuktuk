/*
 *  File name: problem.c
 *
 *  Author: Francisco e Joel
 *
 *  date: 2018/11
 *
 *  Description: C-Implementation of problem related functions
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "problem.h"

#define DEBUG				 0

#define MAXSTRING			 100
#define VARIANTANPOINTS      2
#define MAXRPOINTS   	     8

/*
 *  Função para libertar o problema do tipo problem
 */
void freeProblem(problem pb){
	int i;
	for(i=0; i<pb.l; i++)
		free(pb.city[i]);
	free(pb.city);
	free(pb.points);
}

/*
 *  Função para alocar memória para o número de pontos propostos pelo problema
 *  e da matriz do mapa das cidades
 */
problem allocateProblem(problem pb){
	int i;

	pb.points = (point *) malloc(pb.nPoints * sizeof(point));
	checkMalloc(pb.points);

	pb.city = (unsigned short **) malloc(pb.l * sizeof(unsigned short*));
	checkMalloc(pb.city);
	for(i=0; i<pb.l; i++){
		pb.city[i] = (unsigned short*) malloc(pb.c * sizeof(unsigned short));
		checkMalloc(pb.city[i]);
	}

	return pb;
}

/*
 *  Função para verificar se o problema tem solução através das regras da quantidade de pontos 
 *  de cada variante, se os pontos pertencem ao mapa de cidades e se os pontos são cidades válidas.
 */
int checkIfProblemHasSolution(problem pb){
	int i,x,y;

	if(pb.obj == 'A' && pb.nPoints != VARIANTANPOINTS){
		if(DEBUG==1)printf("The problem has no solution! -> Objective A must have %d points\n", VARIANTANPOINTS);
    	return -1;
	}

	for(i=0; i<pb.nPoints; i++){
		if(pb.points[i].x < 0 || pb.points[i].y < 0 || pb.points[i].x >= pb.l || pb.points[i].y >= pb.c){
			if(DEBUG==1)printf("The problem has no solution! -> There are invalid points\n");
    		return -1;
		}

		x = pb.points[i].x;
		y = pb.points[i].y;
		if(pb.city[x][y] == 0){
			if(DEBUG==1)printf("The problem has no solution! -> There are inaccessable points\n");
    		return -1;
		}
	}

	if((pb.obj == 'B' && pb.nPoints == 1) || (pb.obj == 'C' && pb.nPoints == 1)){
		if(DEBUG==1)printf("The problem has no solution! -> There is only one point in variant B\n");
    	return -1;
	}

	return 0;
}

/*
 *  Função para obter o custo através do indice
 */
int getWtCoord(int v, problem pb){
	int x = v/pb.c;
	int y = v-(pb.c * x);

	return pb.city[x][y];
}

/*
 *  Função para obter a coordenada x através do indice
 */
int getXCoord(int v, problem pb){
	return v/pb.c;
}

/*
 *  Função para obter a coordenada y através do indice
 */
int getYCoord(int v, problem pb){
	return v - (pb.c * (v/pb.c));
}

/*
 *  Função para obter os pontos adjacentes de um indice
 *  Retorna um vetor com os indices válidos 
 */
void getAdjacentPoints(int p, int *points, problem pb, int *n){
	int i, j=0;
	point pt;

	int X[MAXRPOINTS] = { 1, 1, -1, -2, -2, -1, 2, 2 }; 
    int Y[MAXRPOINTS] = { 2, -2, -2, 1, -1, 2, -1, 1 }; 

	for(i=0; i<MAXRPOINTS ; i++){
		pt.x = getXCoord(p, pb) + X[i];
		pt.y = getYCoord(p, pb) + Y[i];
		if(pt.x >= 0 && pt.x < pb.l && pt.y >= 0 && pt.y < pb.c){
			if(pb.city[pt.x][pt.y] > 0){
				points[j] = getVertexFromCoord(pt, pb);
				j++;
			}
		}
	}
	*n = j;
}

/*
 *  Função para obter o indice através das coordenadas
 */
int getVertexFromCoord(point pt, problem pb){
	return ((pb.c)*pt.x + pt.y);
}

/*
 *  Função para preencher um vetor do tipo vértice com indice e custo
 */
void getAdjIndex(problem pb, int v, int *v_adj, vertice* vect){
	int i;
	int validPoints[MAXRPOINTS];

    getAdjacentPoints(v, validPoints, pb, v_adj);

    for ( i = 0; i < (*v_adj); i++)
    {
    	vect[i].v = validPoints[i];
    	vect[i].wt = getWtCoord(validPoints[i], pb);
    }
}

/*
 *  Função recursiva para obter os todos os indices do passeio
 */
void fillSolution( int *st, int a, solution *sol){

	if (st[a] == -1)
		return;
	fillSolution(st, st[a], sol);
	sol->nSteps ++;
}

/*
 *  Função recursiva para preencher a estruta solução com coordenadas e custos
 */
void fillSolutionPoints(problem pb, int *st, int a, solution *sol, int *aux){
	if (st[a] == -1)
		return;
	fillSolutionPoints(pb, st, st[a], sol, aux);
	sol->points[(*aux)].x = getXCoord(a, pb);
	sol->points[(*aux)].y = getYCoord(a, pb);
	sol->points[(*aux)].wt = pb.city[getXCoord(a, pb)][getYCoord(a, pb)];
	(*aux)++;
}

/*
 *  Função para resolver o problema de variante A
 */
solution solveProblemVariantA(problem pb){
	solution sol;
	int vo, vd, aux=0;  	     /*vo: vértice de origem, vd: vértice de destino*/
	int *st;
	unsigned short *wt;

	sol.l = pb.l;
	sol.c = pb.c;
	sol.obj = pb.obj;
	sol.nPoints = pb.nPoints;

	vo = getVertexFromCoord(pb.points[0], pb); /* dá o index das coordenadas do ponto de origem*/
	vd = getVertexFromCoord(pb.points[1], pb); /* dá o index das coordenadas do ponto de destino*/

	if(vo == vd){
		sol.cost = 0;
		sol.nSteps = 0;
		return sol;
	}

	st = (int *) malloc((pb.c * pb.l) * sizeof(int));
	wt = (unsigned short *) malloc((pb.c * pb.l) * sizeof(unsigned short));

	GRAPHpfs(vo, st, wt, vd, pb);

	if(st[vd] == -1){    /*sem solução*/
		sol.cost = -1;
		sol.nSteps = 0;
	} else {
		sol.cost = wt[vd];
		sol.nSteps = 0;

		fillSolution(st, vd, &sol);

		sol.points = (cell *) malloc(sol.nSteps * sizeof(cell));

		fillSolutionPoints(pb, st, vd, &sol, &aux);
	}

	free(st);
	free(wt);

	return sol;
}

/*
 *  Função para resolver o problema de variante B
 */
solution solveProblemVariantB(problem pb){
	solution sol;
	int i, vo, vd, aux=0, nSteps=0;

	int *st;
	unsigned short *wt;

	sol.l = pb.l;
	sol.c = pb.c;
	sol.obj = pb.obj;
	sol.nPoints = pb.nPoints;
	sol.cost = 0;
	sol.nSteps = 0;

	st = ( int *) malloc((pb.c*pb.l) * sizeof( int));
	wt = (unsigned short *) malloc((pb.c*pb.l) * sizeof(unsigned short));


	for(i=0; i<pb.nPoints - 1; i++){
		vo = getVertexFromCoord(pb.points[i], pb);
		vd = getVertexFromCoord(pb.points[i+1], pb);

		GRAPHpfs(vo, st, wt, vd, pb);

		if(st[vd] == -1){
			sol.cost = -1;
			if(nSteps > 0)
				free(sol.points);
			sol.nSteps = 0;
			free(st);
			free(wt);
			return sol;
		}

		if(vo != vd){
			sol.cost += wt[vd];

			fillSolution(st, vd, &sol);

			nSteps += sol.nSteps;

			if(i==0)
				sol.points = (cell *) malloc(nSteps * sizeof(cell));
			else
				sol.points = (cell *) realloc(sol.points ,nSteps * sizeof(cell));

			fillSolutionPoints(pb, st, vd, &sol, &aux);

			sol.nSteps = 0;
		}		
	}
	sol.nSteps = nSteps;
	free(st);
	free(wt);
	return sol;
}

/*
 *  Função para resolver o problema de variante C
 */
solution solveProblemVariantC(problem pb){
	solution sol;
	sol.l = pb.l;
	sol.c = pb.c;
	sol.obj = pb.obj;
	sol.nPoints = pb.nPoints;
	sol.cost = -1;
	sol.cost = 0;

	return sol;
}

/*
 *  Função para verificar qual a variante do problema
 *  e invocar as funções para o resolver
 */
solution solveProblem(problem pb){
	solution sol;
	
	if(checkIfProblemHasSolution(pb) == -1){
		sol.l = pb.l;
		sol.c = pb.c;
		sol.obj = pb.obj;
		sol.nPoints = pb.nPoints;
		sol.cost = -1;
		sol.nSteps = 0;

		freeProblem(pb);

		return sol;
	}

	switch(pb.obj){
		case 'A':
			sol = solveProblemVariantA(pb);
			break;

		case 'B':
			sol = solveProblemVariantB(pb);
			break;

		case 'C':
			sol = solveProblemVariantC(pb);
			break;
		
		default:
			if(DEBUG==1)printf("There was an error!\n");
			exit(0);
			break;
	}

	freeProblem(pb);
	return sol;
}

/*
 *  Função para ler o ficheiro, alocar memória e preencher as estruturas de dados
 */
void readFile(FILE* fp, FILE* fSol){
	char *buff;
	problem pb;
	solution sol;
	int i,j,t,z=0;
	buff = (char *) malloc(MAXSTRING * sizeof(char));
	checkMalloc(buff);
	while(fgets(buff, MAXSTRING, fp) != NULL){
		/* Read first line of problem */
		if(sscanf(buff, "%d %d %c %d", &pb.l, &pb.c, &pb.obj, &pb.nPoints) == 4){
			if(pb.obj == 'A' || pb.obj == 'B' || pb.obj == 'C'){
				pb = allocateProblem(pb);
				pb.v = 0;

				for(i=0; i<pb.nPoints; i++){
					z = fscanf(fp, "%d", &pb.points[i].x);
					z = fscanf(fp, "%d", &pb.points[i].y);
				}
				for(i=0; i<pb.l; i++)
					for(j=0; j<pb.c; j++){
						z = fscanf(fp, "%hu", &pb.city[i][j]);						
					}
					
				sol = solveProblem(pb);
			}else{
				sol.l = pb.l;
				sol.c = pb.c;
				sol.obj = pb.obj;
				sol.nPoints = pb.nPoints;
				sol.cost = -1;
				sol.nSteps = 0;

				for(i=0; i<pb.nPoints; i++){
					z = fscanf(fp, "%d", &t);
					z = fscanf(fp, "%d", &t);
				}
				for(i=0; i<pb.l; i++)
					for(j=0; j<pb.c; j++)
						z = fscanf(fp, "%d", &t);
			}
			z=0;
			if(z != 1)
			saveSolution(sol, fSol);
			if(sol.nSteps > 0)
				free(sol.points);
		}
	}
	free(buff);
}































