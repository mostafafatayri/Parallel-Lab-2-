#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define ROW 1000
#define COL 1000

int matrix1[ROW][COL];
int matrix2[ROW][COL];

int result[ROW][COL];

int main()
{
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            matrix1[i][j] = rand() % 10;
            matrix2[i][j] = rand() % 10;
        }
    }

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            for (int k = 0; k < ROW; k++)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    gettimeofday(&end_time, NULL);

    // calculate time difference
    double execution_time = (end_time.tv_sec - start_time.tv_sec) +
                            (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("Execution time: %.6f seconds\n", execution_time);

    return 0;
}
