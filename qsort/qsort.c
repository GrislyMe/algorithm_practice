#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int left, int right) {
    int i = left - 1;
    swap(&arr[(left + right) / 2], &arr[right]);

    for(int j = left; j < right; j ++) {
        if(arr[j] <= arr[right]) {
            i ++;
            swap(&arr[j], &arr[i]);
        }
    }
    swap(&arr[i + 1], &arr[right]);
    return i + 1;
}

void start_sorting(int *arr, int left, int right) {
    if(left < right) {
        int q = partition(arr, left, right);
        start_sorting(arr, left, q - 1);
        start_sorting(arr, q + 1, right);
    }
}

void quick_sort(int *arr, int n) {
    start_sorting(arr, 0, n - 1);
}

int main() {
    int n = 2;
    scanf("%d", &n);
    int arr[n];
    for(int i = 0; i < n; i ++)
        scanf("%d", &arr[i]);
    quick_sort(arr, n);
    for(int i = 0; i < n; i ++)
        printf("%d ", arr[i]);
    printf("\n");
}
