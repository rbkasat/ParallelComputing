/*
 * Contains method to implement 
 * pthreads and implicit parallelism techniques called loop unrolling 
 * alongwith openMP.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <omp.h>
#include <sched.h>
#include "hdr_const.h"

struct arg_struct {
    int row_num;
};

int MULTIPLICANT;
void threaded_loop_unrolling(void *params);

/*Method to create and join given number of POSIX threads*/
void threadedLoopInvoker(int TC) {
    MULTIPLICANT = MATRIX_SIZE / TC;
    pthread_t thread[TC];
    pthread_attr_t attr;
    int rc, joiner;
    long t;
    struct arg_struct args[TC];
    clock_t start_time, end_time;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for (t = 0; t < TC; t++) {
        args[t].row_num = t;
        rc = pthread_create(&thread[t], NULL, threaded_loop_unrolling, (void *) &args[t]);
        if (rc) {
            printf("Cannot create thread \n");
            exit(-1);
        }
    }


    for (joiner = 0; joiner < TC; joiner++) {
        pthread_join(thread[joiner], NULL);
    }

}

/*Method to implement MAtrix multiplication using multi-threading and loop unrolling technique and openMP*/
void threaded_loop_unrolling(void *params) {
    struct arg_struct *obj = (struct arg_struct *) params;
    int row_num = obj->row_num;
    setAffinity(row_num);
    row_num = row_num * MULTIPLICANT;

    int j, k, sum, i;
#pragma omp parallel for default(none) private(i,j,k,sum) shared(M,N,ANS,MULTIPLICANT,row_num)
    for (i = row_num; i < row_num + MULTIPLICANT; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            sum = 0;
            for (k = 0; k < MATRIX_SIZE; k = k + 8) {
                sum = sum + M[i][k] * N[k][j];
                sum = sum + M[i][k + 1] * N[k + 1][j];
                sum = sum + M[i][k + 2] * N[k + 2][j];
                sum = sum + M[i][k + 3] * N[k + 3][j];
                sum = sum + M[i][k + 4] * N[k + 4][j];
                sum = sum + M[i][k + 5] * N[k + 5][j];
                sum = sum + M[i][k + 6] * N[k + 6][j];
                sum = sum + M[i][k + 7] * N[k + 7][j];
                //sum = sum + M[i][k + 8] * N[k + 8][j];
                //sum = sum + M[i][k + 9] * N[k + 9][j];

            }
            ANS[i][j] = sum;
        }
    }
}

