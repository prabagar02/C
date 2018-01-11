#include <stdio.h> 
#include <stdlib.h>
void mat_mult(int ** arr1, int rows1, int cols1, int ** arr2, int rows2, int cols2,  int** arr3)
{
    int i, j, k ;
    for(i = 0; i < rows1; i++ )
    for(k = 0; k < cols2; k++)
    {
        for(j = 0; j < cols1; j++)
        arr3[i][k]  =  arr3[i][k] +  arr1[i] [j]  * arr2[j][k] ;
    }
}
void mat_out(int ** arr, int rows1, int cols2)
{
    int i, k;
    for(i = 0; i < rows1; i++ ){
        for(k = 0; k < cols2; k++)
        {
            printf("%s", " ");
            printf("%d", arr[i][k]);
        }
        printf("\n");
    }
}
int main ()
{
    int r1, c1, r2, c2; int elements1[50], elements2[50];
    FILE *input = fopen("matrixnum.txt", "r");
    int read, count = 0;
    while(fscanf(input, "%d", &read) != EOF){   /* Getting the row and col values from file */
        if (count == 0)
            r1 = read;
        else if (count == 1)
            c1 = read;
        if (count == ((r1*c1) + 2))
            r2 = read;
        else if (count == ((r1*c1) + 3))
            c2 = read;
        count++;
    }
    fclose(input);
    
    int i = 0; count = 0;
    fopen("matrixnum.txt", "r");
     while(fscanf(input, "%d", &read) != EOF){ /* Putting matrix1 numbers in an array */

        if (count < ((r1*c1) + 2) & (count > 1))
        {
           elements1[i] = read;
           i++;
        }
        count++;
    } 
    fclose(input);

    i=0; count = 0;
    fopen("matrixnum.txt", "r");
     while(fscanf(input, "%d", &read) != EOF){  /* Putting matrix2 numbers in an array */

        if (count > ((r1*c1) + 3))
        {
           elements2[i] = read;
           i++;
        }
        count++;
    } 
    fclose(input);
  
    i =0; int j;  /* Allocating arrays pointers */
    int **array1 = (int **)malloc(r1 * sizeof(int *));
    for (i=0; i<r1; i++)
         array1[i] = (int *)malloc(c1 * sizeof(int));
    int **array2 = (int **)malloc(r2 * sizeof(int *));
    for (i=0; i<r2; i++)
         array2[i] = (int *)malloc(c2 * sizeof(int));
    int **array3 = (int **)malloc(r1 * sizeof(int *));
    for (i=0; i<r1; i++)
         array3[i] = (int *)malloc(c2 * sizeof(int));
    
    count = 0;     /* Putting numbers into a matrix 2-d array */
    for (i = 0; i <  r1; i++)
      for (j = 0; j < c1; j++){
         array1[i][j] = elements1[count];
         count++;
      }
    count = 0;
    for (i = 0; i <  r2; i++)
      for (j = 0; j < c2; j++){
         array2[i][j] = elements2[count];
         count++;
      }
    
    mat_mult(array1, r1, c1, array2, r2, c2, array3);
    mat_out(array3, r1, c2);

    return(0);
}
