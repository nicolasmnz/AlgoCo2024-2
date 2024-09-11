#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>

// Genera un vector con elementos en orden aleatorio
std::vector<int> generate_random_array(int size) {
    std::vector<int> array(size);
    std::iota(array.begin(), array.end(), 1); // Llena con valores 1, 2, ..., size
    std::shuffle(array.begin(), array.end(), std::default_random_engine{});
    return array;
}

// Genera un vector con elementos semi-ordenados
std::vector<int> generate_semi_sorted_array(int size) {
    std::vector<int> array = generate_random_array(size);
    std::sort(array.begin(), array.begin() + size / 2); // Ordena la primera mitad
    return array;
}

// Genera un vector con elementos ordenados
std::vector<int> generate_sorted_array(int size) {
    std::vector<int> array(size);
    std::iota(array.begin(), array.end(), 1); // Llena con valores 1, 2, ..., size
    return array;
}

// Genera un vector con elementos en orden inverso
std::vector<int> generate_reverse_sorted_array(int size) {
    std::vector<int> array = generate_sorted_array(size);
    std::reverse(array.begin(), array.end()); // Invierte el vector
    return array;
}

// Función principal para generar datos y escribirlos en un archivo
void generate_data(const std::string& order, int size, int num_arrays) {
    std::string filename = "dataSort_" + order + ".txt";
    std::ofstream outFile(filename);

    if (!outFile) {
        throw std::runtime_error("No se pudo abrir el archivo de salida.");
    }

    auto write_array_to_file = [&](const std::vector<int>& array) {
        for (size_t i = 0; i < array.size(); ++i) {
            outFile << array[i];
            if (i < array.size() - 1) outFile << ",";
        }
        outFile << "\n";
    };

    for (int i = 0; i < num_arrays; ++i) {
        std::vector<int> array;
        if (order == "Random") {
            array = generate_random_array(size);
        } else if (order == "SemiSorted") {
            array = generate_semi_sorted_array(size);
        } else if (order == "Sorted") {
            array = generate_sorted_array(size);
        } else if (order == "ReverseSorted") {
            array = generate_reverse_sorted_array(size);
        } else {
            throw std::invalid_argument("Tipo de orden no válido.");
        }
        write_array_to_file(array);
    }

    outFile.close();
}

int main() {

    generate_data("Random", 1000000, 300);
    generate_data("SemiSorted", 1000000, 300);
    generate_data("Sorted", 1000000, 300);
    generate_data("ReverseSorted", 1000000, 300);

    return 0;
}
