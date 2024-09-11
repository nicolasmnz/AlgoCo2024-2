#ifndef TIMING_HPP
#define TIMING_HPP

#include <chrono>


// Función para medir tiempo de ejecución de cualquier función
template <typename Func>
long long measure_time (Func func) {
    auto start = std::chrono::high_resolution_clock::now();  // Inicio del cronómetro
    func();  // Ejecuta la función
    auto end = std::chrono::high_resolution_clock::now();  // Fin del cronómetro
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();  // Retorna tiempo en microsegundos
}

#endif
