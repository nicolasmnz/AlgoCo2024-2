#include <iostream>
#include <vector>

using namespace std;

void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    
    // Ordenar los tres elementos para encontrar la mediana
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);
    
    return arr[mid];
}

int partition(vector<int>& array, int low, int high) {

    int pivot = medianOfThree(array, low, high);
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(array[i], array[j]);
        }
    }
    
    swap(array[i + 1], array[high]);
    
    return (i + 1);
}

void quickSort(vector<int>& array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

/*
Código modificado para la implementación de arreglos con libreria <vector>, desde la fuente:
    QuickSort (With Code in Python/C++/Java/C). (s. f.). 
    https://www.programiz.com/dsa/quick-sort
*/