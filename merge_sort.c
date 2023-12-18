/*
    based on recursive mergesort algorithm found in
    Sanjoy Dasgupta, Christos Papadimitriou, & Umesh Vazirani,
    Algorithms, (New York: McGraw_Hill Higher Education, 2008),
    section 2.3 "Mergesort", pages 50-51
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

const size_t count = 32767;

int main(int argc, char const *argv[])
{
    // declare arr[ay]
    // initialize with random numbers
    int arr[count];
    srand(time(0));

    printf("Original array: ");
    for (size_t i = 0; i < count; i++)
    {
        arr[i] = rand() % 32767;
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    // run mergesort
    mergeSort(arr, 0, (int)count - 1);

    printf("Sorted   array: ");
    for (size_t i = 0; i < count; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // test that array is sorted
    int last = -1;
    for (size_t i = 0; i < count; i++)
    {
        if (last > arr[i])
        {
            printf("index %zd = %d is out of order\n", i, arr[i]);
            return 1;
        }
        last = arr[i];
    }
    printf("All elements in sorted order: #%zu = %d\n", sizeof(arr)/sizeof(arr[0]), arr[count - 1]);

    return 0;
}

void mergeSort(int arr[], int left, int right)
{
    // repeatively halve array into smaller groups, eventually into individual components
    if (right - left > 0)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        // merge groups
        merge(arr, left, mid, right);
    }
}

// sort & merge adjacent slices of array to 'temp' array
void merge(int arr[], int left, int mid, int right)
{
    int temp[count];
    int midR = mid + 1;
    int tLeft = left;
    int aLeft = left;

    // sort lefthand & righthand of array to 'temp' array
    // one element at a time; Break when one hand is sorted
    while (left <= mid && midR <= right)
    {
        if (arr[left] <= arr[midR])
        {
            temp[tLeft] = arr[left];
            left++;
        }
        else
        {
            temp[tLeft] = arr[midR];
            midR++;
        }
        tLeft++;
    }
    // Combine remainder of OLD-SORTED hand
    // ...whether righthand
    if (left > mid)
    {
        while (midR <= right)
        {
            temp[tLeft] = arr[midR];
            midR++;
            tLeft++;
        }
    }
    // ...or lefthand
    else
    {
        while (left <= mid)
        {
            temp[tLeft] = arr[left];
            left++;
            tLeft++;
        }
    }
    // copy 'temp' array to 'arr'
    for (int i = aLeft; i <= right; i++)
    {
        arr[i] = temp[i];
    }
}

// OLD-SLOW merge method using inplace sorting
// void merge(int arr[], int left, int mid, int right)
// {
//     // sort increasingly larger slices of array
//     int midRight = mid + 1;
//     if (left > mid || midRight > right)
//         return;
//     if (arr[midRight] < arr[left])
//     {
//         int temp = arr[midRight];
//         memcpy(arr + left + 1, arr + left, (midRight - left) * sizeof(int));
//         arr[left] = temp;
//         merge(arr, left + 1, midRight, right);
//     }
//     else
//     {
//         merge(arr, left + 1, mid, right);
//     }
// }
