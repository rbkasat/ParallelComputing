/*
 *Implementation of Strassen's algorithm for matrix multiplication
 */

#include <stdio.h>
#include "hdr_const.h"

void subtract(int size, double (*a)[size], double (*b)[size], double (*ANS)[size]);
void add(int size, double (*a)[size], double (*b)[size], double (*ANS)[size]);
void basic_matrix_multiplication(int size, double (*a)[size], double (*b)[size], double (*ANS)[size]);

/* Method to perform matrix multiplication using Strassen's algorithm*/

void strassens_multiplication(int size, double (*a)[size], double (*b)[size], double (*ANS)[size]) {

    if (size <= 2) {
        basic_matrix_multiplication(size, a, b, ANS);
    } else {

        int split_size = size / 2;

        double a11[split_size][split_size];
        double a12[split_size][split_size];
        double a21[split_size][split_size];
        double a22[split_size][split_size];

        double b11[split_size][split_size];
        double b12[split_size][split_size];
        double b21[split_size][split_size];
        double b22[split_size][split_size];

        double c11[split_size][split_size];
        double c12[split_size][split_size];
        double c21[split_size][split_size];
        double c22[split_size][split_size];

        double m1[split_size][split_size];
        double m2[split_size][split_size];
        double m3[split_size][split_size];
        double m4[split_size][split_size];
        double m5[split_size][split_size];
        double m6[split_size][split_size];
        double m7[split_size][split_size];

        int i = 0;
        int j = 0;
        for (i = 0; i < split_size; i++) {
            for (j = 0; j < split_size; j++) {

                a11[i][j] = a[i][j];
                b11[i][j] = b[i][j];
                a12[i][j] = a[i][j + split_size];
                b12[i][j] = b[i][j + split_size];
                a21[i][j] = a[i + split_size][j];
                b21[i][j] = b[i + split_size][j];
                a22[i][j] = a[i + split_size][j + split_size];
                b22[i][j] = b[i + split_size][j + split_size];
            }

        }


        double result1[size][size], result2[size][size], result3[size][size];

        //m1=(a11+a22)(b11+b22)
        add(split_size, a11, a22, result1);
        add(split_size, b11, b22, result2);
        strassens_multiplication(split_size, result1, result2, m1);

        //m2=(a21+a22)b11
        add(split_size, a21, a22, result1);
        strassens_multiplication(split_size, result1, b11, m2);

        //m3=a11(b12-b22)
        subtract(split_size, b12, b22, result3);
        strassens_multiplication(split_size, a11, result3, m3);

        //m4=a22(b21-b11)
        subtract(split_size, b21, b11, result3);
        strassens_multiplication(split_size, a22, result3, m4);

        //m5=(a11+a12)b22
        add(split_size, a11, a12, result1);
        strassens_multiplication(split_size, result1, b22, m5);

        //m6=(a21-a11)(b11+b12)
        subtract(split_size, a21, a11, result3);
        add(split_size, b11, b12, result1);
        strassens_multiplication(split_size, result3, result1, m6);

        //m7=(a12-a22)(b12+b22)
        subtract(split_size, a12, a22, result3);
        add(split_size, b21, b22, result1);
        strassens_multiplication(split_size, result3, result1, m7);

        // c11=m1+m4+m7-m5
        add(split_size, m1, m4, result1);
        add(split_size, result1, m7, result2);
        subtract(split_size, result2, m5, c11);

        //c12=m3+m5
        add(split_size, m3, m5, c12);

        //c21=m2+m4
        add(split_size, m2, m4, c21);

        //c22=m1+m3+m6-m2
        add(split_size, m1, m3, result1);
        add(split_size, result1, m6, result2);
        subtract(split_size, result2, m2, c22);

        //Combine result to ANS matrix
        int k = 0;

        for (k = 0; k < split_size; k++) {

            for (j = 0; j < split_size; j++) {

                ANS[k][j] = c11[k][j];

                ANS[k][j + split_size] = c12[k][j];

                ANS[k + split_size][j] = c21[k][j];

                ANS[k + split_size][j + split_size] = c22[k][j];

            }

        }

    }

}

/*Method performs matrix subtraction*/
void subtract(int size, double (*a)[size], double (*b)[size], double (*ANS)[size]) {
    int i = 0;
    int j = 0;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            ANS[i][j] = a[i][j] - b[i][j];
        }
    }
}

/*Method performs matrix addition*/
void add(int size, double (*a)[size], double (*b)[size], double (*ANS)[size]) {
    int i = 0;
    int j = 0;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            ANS[i][j] = a[i][j] + b[i][j];
        }
    }
}

/*Method to perform simple matrix multiplication*/

void basic_matrix_multiplication(int size, double (*a)[size], double (*b)[size], double (*ANS)[size]) {
    int i = 0;
    int j = 0;
    int k = 0;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            ANS[i][j] = 0;
            for (k = 0; k < size; k++) {
                ANS[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}
