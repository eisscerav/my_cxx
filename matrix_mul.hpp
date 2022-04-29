#include <iostream>

void matmul(int m , int n, int k, int *A, int *B, int *C)
{
    int idxA;
    int idxB;
    int idxC;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < k; ++j)
        {
            int tmp = 0.0;
            for (int h = 0; h < n; ++h)
            {
                idxA = i*n + h;
                idxB = h*k + j;
                tmp += A[i * n + h] * B[h * k + j];
            }
            idxC = i*k + j;
            C[i * k + j] = tmp;
        }
    }
}

void matmul1(int m , int n, int k, int *A, int *B, int *C)
{
    //A = m * k ; B = k * n; C = m *n;
    int idxA;
    int idxB;
    int idxC;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int tmp = 0;
            int tmp1 = 0;
            for (int h = 0; h < k; ++h)
            {
                idxA = i*k + h;
                idxB = h*n + j;
                tmp += A[i * n + h] * B[h * k + j];
                tmp1 += A[i*k + h] * B[h*n + j];
            }
            idxC = i*k + j;
            C[i * k + j] = tmp;
        }
    }
}

void computeMatMul()
{
    int m = 4;
    int n = 4;
    int k = 3;

    int a[m*k];
    int b[k*n];
    int c[m*n];
    for(int i = 0; i < m*k; i++)
    {
        a[i] = i;
        b[i] = i+2;
    }

    matmul(m, k, n, a, b, c);
    matmul1(m, n, k, a, b, c);

}
