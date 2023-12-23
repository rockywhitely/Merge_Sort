/* Quicksort algorithm based on Tim Roughgarden,
   Algorithms Illuminated: Part 1: The Basics,
   pp. 126-127, 132 & 154
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int A[], int l, int r);
void quicksort_init(int A[], int length);
void quicksort(int A[], int l, int r);
void swap(int *a, int *b);
int choosePivot(int l, int r);

int main()
{
    // create a array with randomized values & order of elements
    int length = 64;
    int a[length];

    // display maximum of 100 elements for comparison purposes
    srand(time(NULL));
    int squared = length * length;
    int mn = length <= 100 ? length : 100;
    for (int i = 0; i < mn; i++)
    {
        a[i] = rand() % (squared);
        if (i < 100)
            printf("%d ", a[i]);
    }
    printf("\n\n");

    // use quicksort to sort the array
    quicksort_init(a, length);

    // print out the array to ensure it has been sorted
    for (int i = 0; i < mn; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int choosePivot(int l, int r)
{
    return l + rand() % (r - l);
}

int partition(int A[], int l, int r)
{
    int pivot = A[l];
    int i = l + 1;
    for (int j = l + 1; j <= r; j++)
    {
        if (A[j] < pivot)
        {
            if (i != j)
            {
                swap(&A[j], &A[i]);
            }
            i++;
        }
    }
    swap(&A[l], &A[i - 1]);
    return i - 1;
}

void quicksort(int A[], int l, int r)
{
    if (l >= r)
        return;
    int i = choosePivot(l, r);
    swap(&A[l], &A[i]);
    int j = partition(A, l, r);
    quicksort(A, l, j - 1);
    quicksort(A, j + 1, r);
}

void quicksort_init(int A[], int length)
{
    quicksort(A, 0, length - 1);
}
