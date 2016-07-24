/*
 * Contains method to implement matrix multiplication using posix threads 
 * and then assigns each thread to CPU cores dynamically 
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <omp.h>
#include <sched.h>
#include "hdr_const.h"

struct arg_struct {
    int row_num;
};

int MULTIPLICANT;
void threaded_basic(void *params);

//Method to create and join pthreads

void threadedBasicInvoker(int TC) {
    MULTIPLICANT = MATRIX_SIZE / TC;
    pthread_t thread[TC];
    pthread_attr_t attr;
    int rc, joiner;
    long t;
    void *status;
    struct arg_struct args[TC];
    time_t current_time, last_time;
    current_time = time(NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for (t = 0; t < TC; t++) {
        args[t].row_num = t;
        rc = pthread_create(&thread[t], NULL, threaded_basic, (void *) &args[t]);
        if (rc) {
            printf("Cannot create thread \n");
            exit(-1);
        }
    }
    for (joiner = 0; joiner < TC; joiner++) {
        pthread_join(thread[joiner], NULL);
    }

}

/*Method to multiply matrices using multi-threading and OpenMP*/
void threaded_basic(void *params) {

    struct arg_struct *obj = (struct arg_struct *) params;
    int row_num = obj->row_num;
    setAffinity(row_num);
    row_num = row_num * MULTIPLICANT;
    int j = 0;
    int k = 0;
    int sum = 0;
    int c = 0;
#pragma omp parallel for default(none) private(c,j,k,sum) shared(M,N,ANS,MULTIPLICANT,row_num)
    for (c = row_num; c < row_num + MULTIPLICANT; c++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            sum = 0;
            for (k = 0; k < MATRIX_SIZE; k++)
                sum = sum + M[c][k] * N[k][j];
            ANS[c][j] = sum;
        }
    }


}


