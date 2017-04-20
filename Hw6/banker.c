#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int n_processes;
    int n_resources;

    printf("Enter the number of processes: ");
    scanf("%d", &n_processes);
    
    printf("Enter the number of resources: ");
    scanf("%d", &n_resources);
    
    int count = n_processes;
    int running[n_processes];
    for (int i = 0; i < n_processes; i++)
    {
        running[i] = 1;
    }
    
    int max_resource_vector[n_resources];
    printf("Enter the max resource vector: ");
    for (int i = 0; i < n_resources; i++)
    {
        scanf("%d", &max_resource_vector[i]);
    }

    int current_allocation_table[n_processes][n_resources];
    printf("Enter the current resource allocation table: ");
    for (int i = 0; i < n_processes; i++)
    {
        for (int j = 0; j < n_resources; j++)
        {
            scanf("%d", &current_allocation_table[i][j]);
            max_resource_vector[j] -= current_allocation_table[i][j];
        }
    }

    int max_resource_table[n_processes][n_resources];
    printf("Enter the maximum resource claim table: ");
    for (int i = 0; i < n_processes; i++)
    {
        for (int j = 0; j < n_resources; j++)
        {
            scanf("%d", &max_resource_table[i][j]);
        }
    }
    
    int available_table[n_processes][n_resources];
    for (int i = 0; i < n_processes; i++)
    {
        for (int j = 0; j < n_resources; j++)
        {
            available_table[i][j] = max_resource_table[i][j] - current_allocation_table[i][j];
        }
    }
    bool safe = false;
    while( count != 0)
    {
        safe = false;
        for (int i = 0; i < n_processes; i++)
        {
            bool process_successful = true;
            if (running[i] == 1)
            {
                for (int j = 0; j < n_resources; j++)
                {
                    if ( available_table[i][j] > max_resource_vector[j] )
                    {
                        process_successful = false;
                    }
                }
            
                if (process_successful == true)
                {
                    printf("Process %d succeeded\n", i);
                    running[i] = 0;
                    count -= 1;
                    safe = true;
                    for (int j = 0; j < n_resources; j++)
                    {
                        max_resource_vector[j] += current_allocation_table[i][j];
                    }
                }
            }
        }
        if (safe == false)
        {
            printf("The system is in an unsafe state");
            break;
        }
    }
    
    if (safe)
    {
        printf("The system is in a safe state");
    }
    printf("\n");
    return 0;

}
