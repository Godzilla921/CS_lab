/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

void transpose_32_32(int M, int N, int A[N][M], int B[M][N]){
    int i, j ,k;
    int a0, a1, a2, a3, a4, a5, a6, a7;
    for(i=0; i<N ;i+=8){
        for(j=0; j<M; j+=8){
            for(k=i; k<i+8; k++){
                a0 = A[k][j];
                a1 = A[k][j + 1];
                a2 = A[k][j + 2];
                a3 = A[k][j + 3];
                a4 = A[k][j + 4];
                a5 = A[k][j + 5];
                a6 = A[k][j + 6];
                a7 = A[k][j + 7];
                B[j][k] = a0;
                B[j+1][k] = a1;
                B[j+2][k] = a2;
                B[j+3][k] = a3;
                B[j+4][k] = a4;
                B[j+5][k] = a5;
                B[j+6][k] = a6;
                B[j+7][k] = a7;
            }
        }
    }
}
void transpose_64_64(int M, int N, int A[N][M], int B[M][N]){
     int a0, a1, a2, a3, a4, a5, a6, a7;
    int i, j, k;
    int tmp;
    for (i = 0; i < N; i += 8) {
        for (j = 0; j < M; j += 8){
            // 先划分出8X8大块
            // 对前两个4X4矩阵,即第1与第2个
            for (k = i; k < i + 4; k++) {
                // 缓冲A的一行八个数据到局部变量a0-a7中
                a0 = A[k][j];
                a1 = A[k][j + 1];
                a2 = A[k][j + 2];
                a3 = A[k][j + 3];
                a4 = A[k][j + 4];
                a5 = A[k][j + 5];
                a6 = A[k][j + 6];
                a7 = A[k][j + 7];
                // 对于矩阵B
                //第一个4X4. B的前四列，正常转置 
                B[j][k] = a0;
                B[j + 1][k] = a1;
                B[j + 2][k] = a2;
                B[j + 3][k] = a3;
                // 第二个4X4，转职后的结果先存放到B的第二个4X4矩阵中（但实际应该在第三个4X4矩阵中）
                B[j][k + 4] = a4;
                B[j + 1][k + 4] = a5;
                B[j + 2][k + 4] = a6;
                B[j + 3][k + 4] = a7;
            }
            // 对后两个4X4矩阵,即第3和第4个
            for (k = j; k < j + 4; k++) {
                // 矩阵A 按列读入局部变量a0-a7中
                // 第3个 4X4
                a0 = A[i + 4][k];
                a1 = A[i + 5][k];
                a2 = A[i + 6][k];
                a3 = A[i + 7][k];
                // 第4个 4X4
                a4 = A[i + 4][k + 4];
                a5 = A[i + 5][k + 4];
                a6 = A[i + 6][k + 4];
                a7 = A[i + 7][k + 4];
                // 交换局部变量与B矩阵第2个4X4子块
                tmp = B[k][i + 4]; B[k][i + 4] = a0; a0 = tmp;
                tmp = B[k][i + 5]; B[k][i + 5] = a1; a1 = tmp;
                tmp = B[k][i + 6]; B[k][i + 6] = a2; a2 = tmp;
                tmp = B[k][i + 7]; B[k][i + 7] = a3; a3 = tmp;
                // B矩阵第3个子块
                B[k + 4][i + 0] = a0;
                B[k + 4][i + 1] = a1;
                B[k + 4][i + 2] = a2;
                B[k + 4][i + 3] = a3;
                // B矩阵第4个子块
                B[k + 4][i + 4 + 0] = a4;
                B[k + 4][i + 4 + 1] = a5;
                B[k + 4][i + 4 + 2] = a6;
                B[k + 4][i + 4 + 3] = a7;
            }
        }
    }
}
void transpose_61_67(int M, int N, int A[N][M], int B[M][N]){
    int i,j,k,l;
    int block  = 16;
    for (i = 0; i < N; i += block) {
        for (j = 0; j < M; j += block) {
            for(k = i; k < N && k < i+block; k++){
                for(l = j; l < M && l < j+block; l++){
                    B[l][k]=A[k][l];
                }
            }
        }
    }
}
/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]){
    if(M == 32){
        transpose_32_32(M, N, A, B);
    }else if(M == 64){
        transpose_64_64(M, N, A, B);
    }else{
        transpose_61_67(M, N, A, B);
    }
}



/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

