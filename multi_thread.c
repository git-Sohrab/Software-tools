#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter=0;
pthread_mutex_t mtx;

void *classA(void *p)
{
    int i;
    counter=0;
    pthread_mutex_lock(&mtx);
    for (i=0;i<5;i++)
        printf("thread A has counter at %d\n", (counter=i));
    pthread_mutex_unlock(&mtx);

}

void *classB(void *p)
{

    int i;
    counter=0;
    pthread_mutex_lock(&mtx);
    for (i=0;i<5;i++)
        printf("thread B has counter at %d\n", (counter=i));
    pthread_mutex_unlock(&mtx);
}

void *classC(void *p)
{

    int i;
    counter=0;
    pthread_mutex_lock(&mtx);
    for (i=0;i<5;i++)
        printf("thread C has counter at %d\n", (counter=i));
    pthread_mutex_unlock(&mtx);
}

int main(int argc, char **argv)
{
    pthread_t classAThd[2];
    pthread_t classBThd[2];
    pthread_t classCThd[2];

    pthread_mutex_init(&mtx, NULL);
    pthread_create(&classAThd[0], NULL, &classA, NULL);
    pthread_create(&classAThd[1], NULL, &classA, NULL);
    pthread_create(&classBThd[0], NULL, &classB, NULL);
    pthread_create(&classBThd[1], NULL, &classB, NULL);
    pthread_create(&classCThd[0], NULL, &classC, NULL);
    pthread_create(&classCThd[1], NULL, &classC, NULL);

    pthread_join(classAThd[0], NULL);
    pthread_join(classAThd[1], NULL);
    pthread_join(classBThd[0], NULL);
    pthread_join(classBThd[1], NULL);
    pthread_join(classCThd[0], NULL);
    pthread_join(classCThd[1], NULL);

    pthread_mutex_destroy(&mtx);

    return 0;

}
