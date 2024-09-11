#include "selection-sort.hpp"

void selectionSort (vector<int>& array) {
    int size = array.size();

    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[min_idx])
                min_idx = j;
        }
        
        if (min_idx != i)
            swap(array[min_idx], array[i]);
    }
}



/*
Código modificado para la implementación de arreglos con libreria <vector>, desde la fuente:
    Selection Sort (With Code in Python/C++/Java/C). (s. f.). 
    https://www.programiz.com/dsa/selection-sort
*/