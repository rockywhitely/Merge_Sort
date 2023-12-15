/*
    Time Comparison of Three Sort Routines

    merge_sort:
    based on recursive mergesort algorithm found in
    Sanjoy Dasgupta, Christos Papadimitriou, & Umesh Vazirani,
    Algorithms, (New York: McGraw_Hill Higher Education, 2008),
    section 2.3 "Mergesort", pages 50-51

    mergesort & qsort (stdlib.h)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void merge_sort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
int compare(const void *x, const void *y);
void print_results(int arr[], long *start_time, long *end_time, char name[]);

const size_t count = 32767;

int main(int argc, char const *argv[])
{
    long start_time, end_time;
    double elapsed;
    // declare arr[ay]
    // initialize with random numbers
    int arr[count];
    int arrB[count];
    int arrC[count];
    srand(time(0));

    int num;
    for (size_t i = 0; i < count; i++)
    {
        num = rand() % 32767;
        arr[i] = num;
        arrB[i] = num;
        arrC[i] = num;
    }

    start_time = clock();
    qsort(arrC, count, sizeof(int), compare);
    end_time = clock();
    print_results(arrC, &start_time, &end_time, "QSORT in stdlib.h\t\t  ");

    start_time = clock();
    int result = mergesort(arrB, count, sizeof(int), compare);
    end_time = clock();
    print_results(arrB, &start_time, &end_time, "MERGESORT in stdlib.h\t\t  ");

    start_time = clock();
    merge_sort(arr, 0, (int)count - 1);
    end_time = clock();
    print_results(arr, &start_time, &end_time, "Recursive MERGESORT (inplace array)");

    return 0;
}

void merge_sort(int arr[], int left, int right)
{
    // repeatively halve array into smaller groups, eventually into individual components
    if (right - left > 0)
    {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        // merge groups
        merge(arr, left, mid, right);
    }
}

void merge(int arr[], int left, int mid, int right)
{
    // sort increasingly larger slices of array
    int midRight = mid + 1;
    if (left > mid || midRight > right)
        return;
    if (arr[midRight] < arr[left])
    {
        int temp = arr[midRight];
        memcpy(arr + left + 1, arr + left, (midRight - left) * sizeof(int));
        arr[left] = temp;
        merge(arr, left + 1, midRight, right);
    }
    else
    {
        merge(arr, left + 1, mid, right);
    }
}

int compare(const void *x, const void *y)
{
    return (*(int *)(x) - *(int *)(y));
}

void print_results(int arr[], long *start_time, long *end_time, char name[])
{
    double elapsed = (*end_time - *start_time) * 1000.0 / CLOCKS_PER_SEC;
    printf("%s:\t%6.3f ms\n", name, elapsed);

    // test that array is sorted
    int last = -1;
    for (size_t i = 0; i < count; i++)
    {
        if (last > arr[i])
        {
            printf("index %zd = %d is out of order\n", i, arr[i]);
            return;
        }
        last = arr[i];
    }
    printf("All elements in sorted order: #%zu = %d\n", count, arr[count - 1]);

    printf("Last 10 elements: ");
    for (size_t i = count - 10; i < count; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}