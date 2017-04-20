#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <float.h>

static int count = 0;
pthread_mutex_t mutex;
float min = FLT_MAX;
float max = FLT_MIN;
float sum;

struct thread {
    float* value;
};

void *process_numbers(void *arg)
{
    struct thread *t_arg = (struct thread*) arg;
    while(1)
    {
        pthread_mutex_lock(&mutex); 
        if (scanf("%g", t_arg->value) != EOF)
        {
            sum += *t_arg->value;
            count +=1;

            if (*t_arg->value < min)
                min = *t_arg->value;
            
            if (*t_arg->value > max)
                max = *t_arg->value;
            
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
}

int main()
{
    float average;
    pthread_mutex_init(&mutex,NULL);
    pthread_t threads[3];
    struct thread thread_array[4];

    for (int i=0; i< 4; i++)
    {
        thread_array[i].value = malloc(sizeof(float));
    }
    
    for (int i=0; i < 4; i++)
    {
        pthread_create(&threads[i], NULL, process_numbers, (void*)&thread_array[i]);
    }

    for (int i=0; i < 3; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    average = sum/count;
    printf("max: %g\nmin: %g\naverage: %g\n",max,min,average);
    
    for (int i=0; i < 4; i++)
    {
        free(thread_array[i].value);
    }
    
    return 0;
}
