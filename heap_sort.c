#include<stdio.h>
#include<stdlib.h>
#include "project_header.h"

void heapifyByDuration(struct allpaths arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].duration > arr[largest].duration)
        largest = left;

    if (right < n && arr[right].duration > arr[largest].duration)
        largest = right;

    if (largest != i) {
        struct allpaths temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapifyByDuration(arr, n, largest);
    }
}

void heapSortByDuration(struct allpaths arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyByDuration(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        struct allpaths temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapifyByDuration(arr, i, 0);
    }
}

void heapifyByCost(struct allpaths arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].cost > arr[largest].cost)
        largest = left;

    if (right < n && arr[right].cost > arr[largest].cost)
        largest = right;

    if (largest != i) {
        struct allpaths temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapifyByCost(arr, n, largest);
    }
}

void heapSortByCost(struct allpaths arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyByCost(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        struct allpaths temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapifyByCost(arr, i, 0);
    }
}
