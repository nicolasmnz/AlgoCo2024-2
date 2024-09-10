#include <iostream>
using namespace std;

void swap(int *a, int *b) { 
    //funcion para hacer el cambio entre los elementos en la lista
    int temp = *a;
    *a = *b;
    *b = temp;
}
void selectionSort(int array[], int size) {
    for (int step = 0; step < size - 1; step++) {
        int min_idx = step;
        for (int i = step + 1; i < size; i++) {
            if (array[i] < array[min_idx])
                min_idx = i;
        }

        swap(&array[min_idx], &array[step]);
    }
}

//Código extraído de (Selection Sort (With Code In Python/C++/Java/C), s.f.)