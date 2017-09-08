//
// Created by simon on 17-9-8.
//

#include "../main.h"

static void bubble_sort_test() {
    int A[] = {1, 2, 5, 8, 4, 6, 3, 9, 7, 0};
    int s1 = sizeof(A) / sizeof(int);
    bubble_sort(A, s1);
    for (int i = 0; i < s1; ++i) {
        assert(A[i] == i);
    }

    int B[] = {1, 4, 5, 8, 7, 6, 3, 2, 0};
    int s2 = sizeof(B) / sizeof(int);
    bubble_sort(B, s2);
    for (int i = 0; i < s2; ++i) {
        assert(B[i] == i);
    }
}

static void select_sort_test() {
    int A[] = {5, 4, 1, 8, 2, 6, 0, 9, 7, 3};
    int s1 = sizeof(A) / sizeof(int);
    select_sort(A, s1);
    for (int i = 0; i < s1; ++i) {
        assert(A[i] == i);
    }

    int B[] = {1, 4, 5, 8, 7, 6, 3, 2, 0};
    int s2 = sizeof(B) / sizeof(int);
    select_sort(B, s2);
    for (int i = 0; i < s2; ++i) {
        assert(B[i] == i);
    }
}

static void insert_sort_test() {
    int A[] = {0, 4, 3, 8, 2, 9, 5, 6, 7, 1};
    int s1 = sizeof(A) / sizeof(int);
    insert_sort(A, s1);
    for (int i = 0; i < s1; ++i) {
        assert(A[i] == i);
    }

    int B[] = {1, 4, 5, 8, 7, 6, 3, 2, 0};
    int s2 = sizeof(B) / sizeof(int);
    select_sort(B, s2);
    for (int i = 0; i < s2; ++i) {
        assert(B[i] == i);
    }
}

static void quick_sort_test() {
    int A[] = {1, 9, 5, 8, 7, 6, 3, 2, 4, 0};
    int s1 = sizeof(A) / sizeof(int) - 1;
    quick_sort(A, 0, s1);
    for (int i = 0; i < s1 + 1; ++i) {
        assert(A[i] == i);
    }

    int B[] = {1, 4, 5, 8, 7, 6, 3, 2, 0};
    int s2 = sizeof(B) / sizeof(int) - 1;
    quick_sort(B, 0, s2);
    for (int i = 0; i < s2 + 1; ++i) {
        assert(B[i] == i);
    }
}

static void merge_sort_test() {
    int A[] = {1, 9, 5, 8, 7, 6, 3, 2, 4, 0};
    int s1 = sizeof(A) / sizeof(int) - 1;
    merge_sort(A, 0, s1);
    for (int i = 0; i < s1 + 1; ++i) {
        assert(A[i] == i);
    }

    int B[] = {1, 4, 5, 8, 7, 6, 3, 2, 0};
    int s2 = sizeof(B) / sizeof(int) - 1;
    merge_sort(B, 0, s2);
    for (int i = 0; i < s2 + 1; ++i) {
        assert(B[i] == i);
    }
}

void sort_test() {
    bubble_sort_test();
    select_sort_test();
    insert_sort_test();
    quick_sort_test();
    merge_sort_test();
}