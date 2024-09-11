#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <functional>

#include "selection-sort.hpp"
#include "merge-sort.hpp"
#include "quick-sort.hpp"

#include "timing.hpp"   // Incluye el archivo que mide tiempos

std::vector<int> parse_line_to_array (const std::string &line) {
    std::vector<int> array;
    std::stringstream ss(line);
    int value;
    while (ss >> value) {
        array.push_back(value);
        if (ss.peek() == ',') ss.ignore();
    }
    return array;
}

int main () {
    std::ifstream inputFile("dataSort_Random.txt");  // Archivo con múltiples entradas
    std::ofstream outputFile("timingSort_results.csv");  // Archivo para guardar los resultados
    outputFile << "Entrada,Algoritmo,Tiempo (microsegundos)\n";  // Encabezado del CSV
    
    std::string line;

    // Leer las entradas del archivo
    while (getline(inputFile, line)) {
        
        std::vector<int> array = parse_line_to_array(line);  

        // Hacer copias del array para cada algoritmo
        std::vector<int> array_for_selection = array;
        std::vector<int> array_for_quick = array;
        std::vector<int> array_for_merge = array;

        // Medir el tiempo de cada algoritmo
        auto selection_time = measure_time([&]() { selectionSort(array_for_selection); });
        auto quick_time = measure_time([&]() { quickSort(array_for_quick, 0, array_for_quick.size() - 1); });
        auto merge_time = measure_time([&]() { mergeSort(array_for_merge, 0, array_for_merge.size() - 1); });

        // Guardar los resultados en el archivo CSV
        outputFile << array.size() << ",selection-sort," << selection_time << "\n";
        outputFile << array.size() << ",quick-sort," << quick_time << "\n";
        outputFile << array.size() << ",merge-sort," << merge_time << "\n";
    }

    inputFile.close();
    outputFile.close();

    return 0;
}