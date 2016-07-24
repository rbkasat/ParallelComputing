/*
 Contains method to implement matrix multiplication using 
 * implicit parallelism technique called loop unrolling
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <sched.h>
#include "hdr_const.h"

double time_difference;

/*Method to perform matrix multiplication with loop unrolling technique*/
void mulitiply_loop_unrolling() {

    int i = 0;
    int j = 0;
    int k = 0;
    int sum = 0;
    for (i = 0; i < MATRIX_SIZE; i++) {
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

