/*
 * quicksort.c
 *
 *  Created on: 06.11.2017
 *      Author: Gregor
 */

#include "quicksort.h"


void quickSortR(int A[], int links, int rechts);


void quickSort(int n, int A[]) {
    quickSortR(A, 0, n-1);
}
void quickSortR(int A[], int links, int rechts) {

    if (rechts <= links) return;

    int pivot = A[rechts];
    int i = links - 1;
    int j = rechts;

    int t;

    while (1) {

        do { i++; }
        while (A[i] < pivot);

        do { if (j <= i) break;
             j--;
        } while ((A[j] > pivot));

        if (i >= j) break;

        t = A[i];
        A[i] = A[j];
        A[j] = t;

    }

    A[rechts] = A[i];
    A[i] = pivot;

    quickSortR(A, links, i-1);
    quickSortR(A, i+1, rechts);

}
