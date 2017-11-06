/*
 * bubblesort.c
 *
 *  Created on: 07.11.2017
 *      Author: Gregor
 */

#include "bubblesort.h"


void bubbleSort(int n, int A[]) {

    int end, first, second, temp;

    for (end=n; end!=1; end--) {
        for (first=0, second=1; second!=end; first++, second++) {
            if (A[first] > A[second]) {
                temp = A[first];
                A[first] = A[second];
                A[second] = temp;
            }
        }
    }
}
