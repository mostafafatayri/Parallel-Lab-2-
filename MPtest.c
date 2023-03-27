#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ROW 1000
#define COL 1000

int matrix1[ROW][COL];
int matrix2[ROW][COL];
int result[ROW][COL];

int main()
{
    double start_time, end_time;

    // initialize matrices with random values
#pragma omp parallel for
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            matrix1[i][j] = rand() % 10;
            matrix2[i][j] = rand() % 10;
        }
    }

    // get start time
    start_time = omp_get_wtime();

    // matrix multiplication : here we used (parallel to create multiple threads ,
    //and we used for to discompose those for loops into multiple of threads )
    
#pragma omp parallel for collapse(2)
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            int sum = 0;
#pragma omp parallel for reduction(+ \
                                   : sum)  //reduction to perform an addition from different threads and place it in (sum))
            for (int k = 0; k < ROW; k++)
            {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] = sum;
        }
    }

    // get end time
    end_time = omp_get_wtime();

    // final time 
    double execution_time = end_time - start_time;

    printf("Execution time: %.6f seconds\n", execution_time);

    return 0;
}
