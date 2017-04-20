#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "que.h"


static ELE _que[QUE_MAX];
static int _front = 0, _rear = 0;
extern int producers_working;

static int matches = 0;
pthread_mutex_t mutex, enq_mutex, deq_mutex;
sem_t full, empty;

void add_match()
{
    //Note: you will need to lock this update because it is a race condition
    pthread_mutex_lock(&mutex);
    matches++;
    pthread_mutex_unlock(&mutex);
}

void report_matches(char *pattern)
{
    printf("Found %d total matches of '%s'\n", matches, pattern);
}

int que_init()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&enq_mutex, NULL);
    pthread_mutex_init(&deq_mutex, NULL);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, (QUE_MAX-1));
    
}

void que_error(char *msg)
{
    fprintf(stderr, "***** Error: %s\n", msg);
    // exit(-1);
}

int que_is_full()
{
    return (_rear + 1) % QUE_MAX == _front; /* this is why one slot is unused */
}

int que_is_empty()
{
    return _front == _rear;
}

void que_enq(ELE v)
{
    // replace this spin with something better.....
    sem_wait(&empty);
    pthread_mutex_lock(&enq_mutex);

    if ( que_is_full() )
        que_error("enq on full queue");
    _que[_rear++] = v;
    if ( _rear >= QUE_MAX )
        _rear = 0;

    pthread_mutex_unlock(&enq_mutex);
    sem_post(&full);
}

ELE que_deq()
{
    // replace this spin with something better.....
    int try_wait = 1;
    while (try_wait != 0)
    {
        try_wait = sem_trywait(&full);
        if (try_wait != 0 && producers_working == 0)
        {
            pthread_exit(NULL);
        }
    }
    pthread_mutex_lock(&deq_mutex);

    if ( que_is_empty() )
        que_error("deq on empty queue");    
    ELE ret = _que[_front++];
    if ( _front >= QUE_MAX )
        _front = 0;

    pthread_mutex_unlock(&deq_mutex);
    sem_post(&empty);
    return ret;
}

/*
int main()
{
    for ( int i=0; i<QUE_MAX-1; ++i )
    {
        Buffer b;
        sprintf(&b.string, "%d", i);
        que_enq(b);
    }
    while ( !que_is_empty() )
        printf("%s ", que_deq().string);
    putchar('\n');
}*/
