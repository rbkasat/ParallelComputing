/*
 Header file to hold all global variable and shared constants and method signature.
 */

/* 
 * File:   HDR_CONST.h
 * Author: Ankita Dahad
 *
 * Created on 24 July 2016, 00:34
 */


#ifndef HDR_CONST_H
#define HDR_CONST_H

#define _GNU_SOURCE
#define _USE_GNU
#include <pthread.h>
#include "sched.h"

//Matrix size as a power of 2(Because of Strassen's limitation)
#define MATRIX_SIZE 128
#define CPU_CORE 4

/*Method to associate a given thread to a CPU core*/
void setAffinity(int core_id) ;
//Input Matrices : M and N
//Result Matrix :ANS
static double M[MATRIX_SIZE][MATRIX_SIZE];
static double ANS[MATRIX_SIZE][MATRIX_SIZE];
static double N[MATRIX_SIZE][MATRIX_SIZE];


#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* HDR_CONST_H */



