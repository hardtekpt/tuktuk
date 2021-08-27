/*
 *  File name: file.h
 *
 *  Author: Francisco e Joel
 *
 *  date: 2018/11
 *
 *  Description: Header file for file functions
 *
 */

#ifndef UtilsHeader
#define UtilsHeader

#include "utils.h"
#include "problem.h"

void usage();

FILE* openFile(char* fileName, char mode, char* extension);
void saveSolution(solution sol, FILE* fSol);


#endif


