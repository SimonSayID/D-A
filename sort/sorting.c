//
// Created by simon on 17-9-8.
//

#include "../main.h"

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

static void merge(int *A, int *temp, int l_pos, int r_pos, int right_end) {
    int left_end = r_pos - 1;
    int tmp = l_pos;
    int nelem = right_end - l_pos + 1;

    while (l_pos <= left_end && r_pos <= right_end) {
        if (A[l_pos] <= A[r_pos]) {
            temp[tmp++] = A[l_pos++];
        } else {
            temp[tmp++] = A[r_pos++];
        }
    }

    while (l_pos <= left_end) {
        temp[tmp++] = A[l_pos++];
    }
    while (r_pos <= right_end) {
        temp[tmp++] = A[r_pos++];
    }

    for (int i = 0; i < nelem; ++i, --right_end) {
        A[right_end] = temp[right_end];
    }
}

static void msort(int *A, int *temp, int left, int right) {
    int center;
    if (left < right) {
        center = (left + right) / 2;
        msort(A, temp, left, center);
        msort(A, temp, center + 1, right);
        merge(A, temp, left, center + 1, right);
    }
}

void merge_sort(int *A, int left, int right) {
    int size = right - left;
    int *temp = malloc(size * sizeof(int));
    if (temp != NULL) {
        msort(A, temp, left, right);
        free(temp);
    } else {
        perror("merge_sort");
    }
}