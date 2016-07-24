/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HDR_CONST.h
 * Author: Ankita
 *
 * Created on 24 July 2016, 00:34
 */


#ifndef HDR_CONST_H
#define HDR_CONST_H

#define _GNU_SOURCE
#define _USE_GNU
#include <pthread.h>
#include "sched.h"

#define MATRIX_SIZE 128
//#define TC 4
#define CPU_CORE 4

void setAffinity(int core_id) ;
static double M[MATRIX_SIZE][MATRIX_SIZE];
static double ANS[MATRIX_SIZE][MATRIX_SIZE];
static double N[MATRIX_SIZE][MATRIX_SIZE];

//static void setAffinity(int core_id) {
//    int num_cores = 4;
//
//    core_id = core_id % num_cores;
//    if (core_id < 0 || core_id >= num_cores)
//        return;
//    cpu_set_t cpuset;
//    CPU_ZERO(&cpuset);
//    CPU_SET(core_id, &cpuset);
//    pthread_t current_thread = pthread_self();
//    pthread_setaffinity_np(current_thread, sizeof (cpu_set_t), &cpuset);
//
//}

#ifdef __cplusplus
extern "C" {
#endif

   // const int MATRIX_SIZE=8192;
    //const int CPU_CORE=4;
    //const int TC = 4;
    
    


#ifdef __cplusplus
}
#endif

#endif /* HDR_CONST_H */

/*Method to associate a given thread to a CPU core*/

