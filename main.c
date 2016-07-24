/* 
 * File:   main.c
 * Author: Ankita Dahad
 *
 * Created on 23 July 2016, 23:53
 * Entry point of the project which executes various approaches of 
 * matrix multiplication and compares their performance against the basic
 * matrix multiplication time.
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


#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
int MULTIPLICANT;
int TC;
double time_difference;
void mulitiply_basic();
void initialize_matrix(int size, double (*matrix)[size]);
void print_mat(double m[][MATRIX_SIZE]);
void timestamp();

struct arg_struct {
    int row_num;
};

int main(int argc, char** argv) {
    printf("Type in a number of threads in pow of 2 \n");
    scanf("%d", &TC);

    MULTIPLICANT = MATRIX_SIZE / TC;
    long timeval = 0;
    initialize_matrix(MATRIX_SIZE, M);
    initialize_matrix(MATRIX_SIZE, N);

    //basic matrix multiplication
    timeval = (unsigned long) time(NULL);
    mulitiply_basic();
    timeval = ((unsigned long) time(NULL)) - timeval;
    printf("\nFinished! Simple matrix multiplication: %ld seconds. \n", timeval);

    //matrix multiplication using loop  unrollign
    timeval = (unsigned long) time(NULL);
    mulitiply_loop_unrolling(M, N, ANS);
    timeval = ((unsigned long) time(NULL)) - timeval;
    printf("\nFinished! Simple loop matrix multiplication: %ld seconds. \n", timeval);

    //multithreaded matrix multiplication
    timeval = (unsigned long) time(NULL);
    threadedBasicInvoker(TC);
    timeval = ((unsigned long) time(NULL)) - timeval;
    printf("\nFinished! MultiThreaded matrix multiplication: %ld seconds. \n", timeval);

    //multithreded matrix multiplication combined with loop unrolling
    timeval = (unsigned long) time(NULL);
    threadedLoopInvoker(TC);
    timeval = ((unsigned long) time(NULL)) - timeval;
    printf("\nFinished! Unrolling MultiThreaded matrix multiplication: %ld seconds. \n", timeval);
    timeval = (unsigned long) time(NULL);

    //Strassen's algorithm for matrix multiplication
    timeval = (unsigned long) time(NULL);
    strassens_multiplication(MATRIX_SIZE, M, N, ANS);
    timeval = ((unsigned long) time(NULL)) - timeval;
    printf("\nFinished! Strassens matrix multiplication: %ld seconds. \n", timeval);


}

/*
 Method to perform basic matrix multiplication
 */
void mulitiply_basic() {

    int i, j, k, sum;
    {
        for (i = 0; i < MATRIX_SIZE; i++) {
            {
                for (j = 0; j < MATRIX_SIZE; j++) {
                    sum = 0;
                    {
                        for (k = 0; k < MATRIX_SIZE; k++)
                            sum = sum + M[i][k] * N[k][j];
                        ANS[i][j] = sum;
                    }
                }
            }
        }
    }
}

/*Method to print given 2-dimensional matrix*/
void print_mat(double m[][MATRIX_SIZE]) {
    int i;
    int j;
    printf("\n");
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            printf("%f ", m[i][j]);
        }
        printf("\n");
    }

}

//Method to fill given matrix with random generated numbers

void initialize_matrix(int size, double (*matrix)[size]) {
    int i = 0;
    int j = 0;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            matrix[i][j] = rand() % 5;
        }
    }
}

/*
 * Method to bind posix threads to different cores of the cpu 
 * to get maximum cpu utilization
 */
void setAffinity(int core_id) {

    core_id = core_id % CPU_CORE;
    if (core_id < 0 || core_id >= CPU_CORE)
        return;
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);
    pthread_t current_thread = pthread_self();
    pthread_setaffinity_np(current_thread, sizeof (cpu_set_t), &cpuset);

}

/*Method to get current timestamp*/
void timestamp() {
    time_t ltime;
    ltime = time(NULL);
    printf("\ncurrent time%s\n", asctime(localtime(&ltime)));
}