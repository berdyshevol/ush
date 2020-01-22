#include "libmx.h"

static int comparator(char *s1, char *s2);
static void swap(char **s1, char **s2, int *count);

int mx_quicksort(char **arr, int low, int high) {
    //implimantaion https://www.programcreek.com/2012/11/quicksort-array-in-java/
    if (arr == NULL || *arr == NULL) return -1;
    if (low >= high)
        return 0;
    int count = 0;
    // pick the pivot
    int middle = low + (high - low) / 2;
    char *pivot = arr[middle];

    // make left < pivot and right > pivot
    int i = low;
    int j = high;
    while (i <= j) {
        while (comparator(arr[i], pivot) < 0) {
            i++;
        }

        while (comparator(arr[j], pivot) > 0) {
            j--;
        }

        if (i <= j) {
            swap(&arr[i], &arr[j], &count);
            i++;
            j--;
        }
    }

    // recursively sort two sub parts
    if (low < j)
        count += mx_quicksort(arr, low, j);

    if (high > i)
        count += mx_quicksort(arr, i, high);
    
    return count;
}

static int comparator(char *s1, char *s2) {
    return mx_strlen(s1) - mx_strlen(s2);
}

static void swap(char **s1, char **s2, int *count) {
    if (comparator(*s1, *s2) == 0) return; // added this
    char *t = *s1; 
    *s1 = *s2;
    *s2 = t;
    (*count)++;                              // for counting shifts
}

