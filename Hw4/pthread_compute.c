#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <float.h>

float min = FLT_MAX;
float max = FLT_MIN;
float sum;

struct thread {
    int start;
    int end;
    float* buffer;
};

void *process_numbers(void *arg)
{
    struct thread *t_arg = (struct thread*) arg;
    
    for (int i = t_arg->start; i < t_arg->end; i++)
    {
        sum += t_arg->buffer[i];
        
        if (t_arg->buffer[i] < min)
            min = t_arg->buffer[i];
        if (t_arg->buffer[i] > max)
            max = t_arg->buffer[i];
    }
}

int main()
{
    float input_buffer[1024];
    float input, average;
    int count = 0;
    
    while(scanf("%g", &input) != EOF)
    {
        input_buffer[count] = input;
        count += 1;
    }
    
    int apt = count / 4; //apt = amount per thread    
    
    pthread_t threads[3];
    struct thread thread_array[4];
    
    for (int i=0; i<4; i++)
    {
        thread_array[i].buffer = input_buffer;

        if (i==0)
        {
            thread_array[i].start = 0;
            thread_array[i].end = apt;
        }
        
        else
        {
            thread_array[i].start = thread_array[i-1].end;
            thread_array[i].end = thread_array[i].start + apt;
        }

        if (count%4 != 0 && i==3)
            thread_array[i].end += (count%4);
    }
    
    for (int i=0; i < 3; i++)
    {
        pthread_create(&threads[i], NULL, process_numbers,(void*)&thread_array[i]);
    }
    
    for (int i = thread_array[3].start; i < thread_array[3].end; i++)
    {
        sum += thread_array[3].buffer[i];
    }

    for (int i=0; i < 3; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
    average = sum/count;
    printf("max: %g\nmin: %g\naverage: %g\n",max,min,average);
    
    return 0;
}
