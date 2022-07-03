#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h> 

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t al = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t ml = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t pl = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tl = PTHREAD_MUTEX_INITIALIZER;

int loop_counter = 0;
int loop_limit = 10;
//AGENT FUNCTION
void* agentFunction() {
    do {
        pthread_mutex_lock(&lock);
        printf("\n");
        int randNum = (rand() % 3) + 1;
        if (randNum == 1) {
            printf("Agent places tobacco on table\n");
            printf("Agent places paper on table\n");
            pthread_mutex_unlock(&ml);
        } else if (randNum == 2) {
            printf("Agent places tobacco on table\n");
            printf("Agent places match on table\n");
            pthread_mutex_unlock(&pl);
        } else {
            printf("Agent places match on table\n");
            printf("Agent places paper on table\n");
            pthread_mutex_unlock(&tl);
        }
        pthread_mutex_unlock(&lock);
        pthread_mutex_lock(&al);
        loop_counter+=1;
    } while(loop_counter < loop_limit);
    return 0;
}

//SMOKER WITH TOBACCO FUNCTION 
void *tobaccoSmokerFunction() {
    int loop_counter = 0;
    do {
        pthread_mutex_lock(&tl);
        pthread_mutex_lock(&lock);
        printf("Smoker with Tobacco Smokes (but doesnt inhale).\n");
        pthread_mutex_unlock(&al);
        pthread_mutex_unlock(&lock);
    } while(loop_counter < loop_limit);
}

//SMOKER WITH MATCH FUNCTION 
void *matchSmokerFunction() {
    int loop_counter = 0;
    do {
        pthread_mutex_lock(&ml);
        pthread_mutex_lock(&lock);
        printf("Smoker with Match Smokes (but doesnt inhale).\n");
        pthread_mutex_unlock(&al);
        pthread_mutex_unlock(&lock);
    } while(loop_counter < loop_limit);
}

//SMOKER WITH PAPER FUNCTION 
void *paperSmokerFunction() {
    int loop_counter = 0;
    do {
        pthread_mutex_lock(&pl);
        pthread_mutex_lock(&lock);
        printf("Smoker with Paper Smokes (but doesnt inhale).\n");
        pthread_mutex_unlock(&al);
        pthread_mutex_unlock(&lock);
    } while(loop_counter < loop_limit);
}

// MAIN FUNCTION
int main() {
    pthread_t agent, tobaccoSmoker, matchSmoker, paperSmoker;

    srand(time(NULL));

    pthread_mutex_lock(&al);
    pthread_mutex_lock(&ml);
    pthread_mutex_lock(&pl);
    pthread_mutex_lock(&tl);
    pthread_mutex_unlock(&lock);

    pthread_create(&agent, 0, &agentFunction, 0);
    pthread_create(&tobaccoSmoker, 0, &tobaccoSmokerFunction, 0);
    pthread_create(&paperSmoker, 0, &paperSmokerFunction, 0);
    pthread_create(&matchSmoker, 0, &matchSmokerFunction, 0);

    pthread_join(agent, 0);

    pthread_mutex_destroy(&lock);
    pthread_mutex_destroy(&al);
    pthread_mutex_destroy(&tl);
    pthread_mutex_destroy(&pl);
    pthread_mutex_destroy(&ml);
    return 0;
}