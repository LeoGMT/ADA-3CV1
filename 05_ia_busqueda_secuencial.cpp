// Solucion estructurada propuesta por IA: busqueda secuencial.
// Adaptada a C++98 para poder compilarse en versiones antiguas de Dev-C++.
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

int numeroAleatorio(int limite) {
    // Combina dos llamadas para funcionar incluso con RAND_MAX pequeno en MinGW antiguo.
    const double base = (double)RAND_MAX + 1.0;
    double valor = ((double)rand() * base + (double)rand()) / (base * base);
    return (int)(valor * limite);
}

bool tamanoPermitido(int n) {
    return n == 1000 || n == 10000 || n == 100000 || n == 1000000 || n == 10000000;
}

vector<int> generarDatos(int n) {
    vector<int> datos(n);
    srand(314159u + (unsigned)n);
    for (int i = 0; i < n; ++i) datos[i] = numeroAleatorio(2 * n);
    return datos;
}

int busquedaSecuencial(const vector<int>& datos, int clave, long long& comparaciones) {
    for (int i = 0; i < (int)datos.size(); ++i) {
        ++comparaciones;
        if (datos[i] == clave) return i;
    }
    return -1;
}

int main() {
    int n;
    cout << "Tamano (1000, 10000, 100000, 1000000 o 10000000): ";
    if (!(cin >> n) || !tamanoPermitido(n)) {
        cerr << "Error: tamano no valido.\n";
        return 1;
    }
    vector<int> datos = generarDatos(n);
    clock_t ordenInicio = clock();
    sort(datos.begin(), datos.end());
    clock_t ordenFin = clock();

    const int clave = 2 * n; // Ausente para provocar recorrido completo.
    int repeticiones = 1000000 / n;
    if (repeticiones < 1) repeticiones = 1;
    long long totalComparaciones = 0;
    volatile int resultado = -1;
    clock_t busquedaInicio = clock();
    for (int r = 0; r < repeticiones; ++r)
        resultado = busquedaSecuencial(datos, clave, totalComparaciones);
    clock_t busquedaFin = clock();

    cout << fixed << setprecision(3)
         << "\n=== BUSQUEDA SECUENCIAL | VERSION IA ===\n"
         << "Elementos: " << n << '\n'
         << "Ordenamiento: " << 1000.0 * (ordenFin - ordenInicio) / CLOCKS_PER_SEC << " ms\n"
         << "Tiempo promedio de busqueda: " << 1000000.0 * (busquedaFin - busquedaInicio) / CLOCKS_PER_SEC / repeticiones << " us\n"
         << "Comparaciones promedio: " << (double)totalComparaciones / repeticiones << '\n'
         << "Resultado: " << (resultado < 0 ? "no encontrado" : "encontrado") << '\n';
    return 0;
}
