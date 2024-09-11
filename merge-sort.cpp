#include "merge-sort.hpp"

void merge (vector<int>& arr, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    
    vector<int> L(n1);
    vector<int> M(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
        
    for (int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];
        
    int i = 0, j = 0, k = p;
    
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }
}
void mergeSort (vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

/*
Código modificado para la implementación de arreglos con libreria <vector>, desde la fuente:
    Merge Sort (With Code in Python/C++/Java/C). (s. f.). 
    https://www.programiz.com/dsa/merge-sort
*/