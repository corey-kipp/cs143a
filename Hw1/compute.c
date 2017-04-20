#include <stdio.h>
#include <stdlib.h>

int main()
{
    float buffer, sum, small, big, average;
    int count = 0;

    while(scanf("%g", &buffer) == 1)
    {
        
        count += 1;
        
        if (count == 1)
        {
            small = buffer;
            big = buffer;
        }
        
        if (buffer < small)
            small = buffer;
        
        if (buffer > big)
            big = buffer;
        
        sum += buffer;
    }
    
    if (count == 0)
    {
        printf("No numbers found in file!\n");
        exit(1);
    }
    
    average = sum/count;

    printf("max: %g\nmin: %g\naverage: %g\n", big, small, average);
    
    return 0;
}
