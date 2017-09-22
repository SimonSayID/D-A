//
// Created by simon on 17-9-8.
//

#include "sort.h"

void bubble_sort(int *A, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N - 1 - i; ++j) {
            if (A[j] > A[j + 1]) {
                int temp = A[j + 1];
                A[j + 1] = A[j];
                A[j] = temp;
            }
        }
    }
}

void select_sort(int *A, int N) {
    for (int j = 0; j < N; ++j) {
        int min = j;
        for (int i = j + 1; i < N; ++i) {
            if (A[i] < A[min]) {
                min = i;
            }
        }
        int temp = A[j];
        A[j] = A[min];
        A[min] = temp;
    }
}

void insert_sort(int *A, int N) {
    for (int j = 1; j < N; ++j) {
        int temp = A[j];
        int i;
        for (i = j; i > 0; --i) {
            if (A[i - 1] > temp) {
                A[i] = A[i - 1];
            } else {
                break;
            }
        }
        A[i] = temp;
    }
}

void quick_sort(int *A, int left, int right) {

    int i = left;
    int j = right;
    int pivot = A[(left + right) / 2];

    while (i <= j) {
        while (A[i] < pivot) {
            i++;
        }
        while (A[j] > pivot) {
            j--;
        }

        if (i <= j) {
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j) {
        quick_sort(A, left, j);
    }
    if (i < right) {
        quick_sort(A, i, right);
    }

}

static void merge(int *A, int left, int right) {
    int i, j, k;
    int *x = malloc(left * sizeof (int));
    for (i = 0, j = right, k = 0; k < left; k++) {
        x[k] = j == left ? A[i++] :
               i == right ? A[j++] :
               A[j] < A[i] ? A[j++] : A[i++];
    }
    for (i = 0; i < left; i++) {
        A[i] = x[i];
    }
    free(x);
}

void merge_sort(int *A, int N) {
    if (N < 2)
        return;
    int center = N / 2;
    merge_sort(A, center);
    merge_sort(A + center, N - center);
    merge(A, N, center);
}

void shell_sort(int *A, int N) {
    int h = 1;
    while (h < N / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (int i = h; i < N; ++i) {
            for (int j = i; j >= h && A[j] <= A[j - h]; j -= h) {
                int temp = A[j];
                A[j] = A[j - h];
                A[j - h] = temp;
            }
        }
        h = h / 3;
    }
}

