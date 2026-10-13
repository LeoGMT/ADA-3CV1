// Solucion estructurada propuesta por IA: busqueda binaria.
// Adaptada a C++98 para Dev-C++ clasico.
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
    const int valores[] = {1000, 10000, 100000, 1000000, 10000000};
    for (int i = 0; i < 5; ++i) if (n == valores[i]) return true;
    return false;
}

vector<int> generarDatos(int n) {
    vector<int> datos(n);
    srand(271828u + (unsigned)n);
    for (int i = 0; i < n; ++i) datos[i] = numeroAleatorio(2 * n);
    return datos;
}

int busquedaBinaria(const vector<int>& datos, int clave, long long& comparaciones) {
    int izquierda = 0;
    int derecha = (int)datos.size() - 1;
    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        ++comparaciones;
        if (datos[medio] == clave) return medio;
        if (datos[medio] < clave) izquierda = medio + 1;
        else derecha = medio - 1;
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

    const int clave = 2 * n;
    const int repeticiones = 100000;
    long long totalComparaciones = 0;
    volatile int resultado = -1;
    clock_t busquedaInicio = clock();
    for (int r = 0; r < repeticiones; ++r)
        resultado = busquedaBinaria(datos, clave, totalComparaciones);
    clock_t busquedaFin = clock();

    cout << fixed << setprecision(3)
         << "\n=== BUSQUEDA BINARIA | VERSION IA ===\n"
         << "Elementos: " << n << '\n'
         << "Ordenamiento: " << 1000.0 * (ordenFin - ordenInicio) / CLOCKS_PER_SEC << " ms\n"
         << "Tiempo promedio de busqueda: " << 1000000.0 * (busquedaFin - busquedaInicio) / CLOCKS_PER_SEC / repeticiones << " us\n"
         << "Comparaciones promedio: " << (double)totalComparaciones / repeticiones << '\n'
         << "Resultado: " << (resultado < 0 ? "no encontrado" : "encontrado") << '\n';
    return 0;
}
