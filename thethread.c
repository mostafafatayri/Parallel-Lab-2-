#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define ROW 1000
#define COL 1000
#define THREADS 6

int matrix1[ROW][COL];
int matrix2[ROW][COL];

int result[ROW][COL];

void *multiplier(void *arg)
{
    int thread_id = *(int *)arg;
    int start = thread_id * ROW / THREADS;
    int end = (thread_id + 1) * ROW / THREADS;

    for (int i = start; i < end; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            for (int k = 0; k < ROW; k++)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main()
{

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    pthread_t threads[THREADS];
    int thread_ids[THREADS];

    // initialize matrices with random values
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            matrix1[i][j] = rand() % 10;
            matrix2[i][j] = rand() % 10;
        }
    }

    // create threads and start multiplication
    for (int i = 0; i < THREADS; i++)
    {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, multiplier, (void *)&thread_ids[i]);
    }

    // wait for threads to finish
    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end_time, NULL);

    // calculate time difference
    double execution_time = (end_time.tv_sec - start_time.tv_sec) +
                            (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("Execution time: %.6f seconds\n", execution_time);

    return 0;
}
