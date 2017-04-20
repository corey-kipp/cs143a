/**
 * CS143a - Fall 2016
 * HW #1
 * @author: Corey Kipp
 *
 * This program reads numbers from a file specified as the only argument,
 * one number per line, and computes the average of all the numbers.
 * The result is printed out on the second line of output, with the first
 * line containing the filename and total number of values read.
 */

// What header file allows us to handle file I/O?
#include <stdio.h>
#include <stdlib.h> // This lets us call exit(...)

int main(int argc, char ** args)
{
    // First, get the filename from the command line arguments if specified
    if (argc < 2)
    {
        printf("Error: no input file specified\nUsage: average numbers.dat\n");
        exit(1);
    }
    char * filename = args[1];
    /* Use this line to verify you got the correct filename:
    printf("Reading numbers from file %s\n", filename);
    */

    // Open the file and verify it opened properly
    FILE * f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Failed to open file!\n");
        exit(2);
    }

    // Declare (and maybe initialize) any necessary variables before reading from the file
    float number, total = 0;
    int count = 0; 

    // Read all the numbers from the file and compute the average
    while (fscanf(f,"%f", &number) == 1)
    {
        total += number;
        count += 1;
    }

  // Some error-checking if the file was empty
    if (count == 0)
    {
        printf("No numbers found in file!\n");
        exit(3);
    }

    // Lastly, print the result
    // NOTE: ensure that the actual average is on the SECOND line all by itself
    // or you may not receive credit for your program!
    float result = total/count;
    printf("The average of the %d numbers in file \"%s\" is:\n%f\n",count,args[1],result);

    // SUCCESS!
    return 0;
}
