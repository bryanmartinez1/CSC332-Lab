#include <stdio.h>
#include <stdlib.h>
#include<time.h>        //time for rand generator
#include "sem.h"		//semaphore
#include <unistd.h>		//fork
#include <sys/types.h>	//kill
#include <sys/wait.h>	//kill, SIGKILL

int main() {
    int smoker_match, smoker_paper, smoker_tobacco, agent, lock;
    int smokerTobacco, smokerMatch, smokerPaper;
    int loop_limit = 10, randomNumber, loop_counter;
//Semaphores made and declared
    smoker_match=semget(IPC_PRIVATE,1,0666 | IPC_CREAT);
    smoker_paper=semget(IPC_PRIVATE,1,0666 | IPC_CREAT);
    smoker_tobacco=semget(IPC_PRIVATE,1,0666 | IPC_CREAT);
    agent=semget(IPC_PRIVATE,1,0666 | IPC_CREAT);
    lock=semget(IPC_PRIVATE,1,0666 | IPC_CREAT);

    sem_create(lock,1);
    sem_create(smoker_match,0);
    sem_create(smoker_paper,0);
    sem_create(smoker_tobacco,0);
    sem_create(agent,0);

//Child Process for Smoker with Tobacco
    smokerTobacco=fork();

    if (smokerTobacco < 0) {
        printf("Error in Fork for Smoker with Tobacco");
        return 0;
    } else if (smokerTobacco == 0) {
        int loop_counter = 0;
        do {
            P(smoker_tobacco);
            P(lock);
            printf("Smoker with Tobacco Pick up match \n");
            printf("Smoker with Tobacco Pick up paper \n");
            V(agent);
            V(lock);
            printf("Smoker with Tobacco Smokes (but dont inhale) \n");
            sleep(1);
            loop_counter +=1;
        } while (loop_counter<loop_limit);
    }

//Child Process for Smoker with Match
    smokerMatch=fork();
    if(smokerMatch < 0) {
        printf("Error in Fork for Smoker with Match");
        return 0;
    } else if(smokerMatch == 0) {
        int loop_counter = 0;
        do {
            P(smoker_match);
            P(lock);
            printf("Smoker with Match Pick up paper \n");
            printf("Smoker with Match Pick up tobacco \n");
            V(agent);
            V(lock);
            printf("Smoker with Match Smokes (but dont inhale) \n");
            sleep(1);
            loop_counter +=1;
        } while (loop_counter<loop_limit);
    }
//Child Process for Smoker with Paper
    smokerPaper=fork();
    if(smokerPaper < 0) {
        printf("Error in Fork for Smoker with Paper");
        return 0;
    } else if(smokerPaper == 0)  {
        int loop_counter = 0;
        do {
            P(smoker_paper);
            P(lock);
            printf("Smoker with Paper Pick up match \n");
            printf("[Smoker with Paper Pick up tobacco \n");
            V(agent);
            V(lock);
            printf("Smoker with Paper Smokes (but dont inhale) \n");
            sleep(1);
            loop_counter +=1;
        } while (loop_counter<loop_limit);
    }

// Agent Process
    srand(time(NULL));
    loop_counter = 0;
    do {
        P(lock);
        randomNumber = rand()%3 +1;
        printf("\n");
        if (randomNumber == 1)
        {
            printf("Agent Put tobacco on table \n");
            printf("Aent Put paper on table \n");
            V(smoker_match);

        }
        else if (randomNumber == 2)
        {
            printf("Agent Put tobacco on table \n");
            printf("Agent Put match on table \n");
            V(smoker_paper);
        }
        else if (randomNumber == 3)
        {
            printf("Agent Put match on table \n");
            printf("Agent Put paper on table \n");
            V(smoker_tobacco);
        }
        V(lock);
        P(agent);
        loop_counter+=1;
    } while (loop_counter<loop_limit);

    kill(smokerTobacco, SIGKILL);
    kill(smokerMatch, SIGKILL);
    kill(smokerPaper, SIGKILL);
    printf("\nAll Smokers and Agent are Sleeping Now\n");

    return 0;
}