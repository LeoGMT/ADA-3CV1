// Solucion estructurada propuesta por IA: busqueda por interpolacion.
// Adaptada a C++98. La clave esta colocada cerca del extremo finito de una distribucion adversaria.
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

bool tamanoPermitido(int n) {
    return n == 1000 || n == 10000 || n == 100000 || n == 1000000 || n == 10000000;
}

vector<long long> generarDatosAdversarios(int n) {
    vector<long long> datos(n);
    for (int i = 0; i < n - 1; ++i) datos[i] = i;
    datos[n - 1] = 1000000000000000000LL;
    srand(161803u + (unsigned)n);
    random_shuffle(datos.begin(), datos.end());
    return datos;
}

int busquedaInterpolacion(const vector<long long>& datos, long long clave, long long& comparaciones) {
    int izquierda = 0;
    int derecha = (int)datos.size() - 1;
    while (izquierda <= derecha && clave >= datos[izquierda] && clave <= datos[derecha]) {
        if (datos[izquierda] == datos[derecha]) {
            ++comparaciones;
            return datos[izquierda] == clave ? izquierda : -1;
        }
        long long numerador = (clave - datos[izquierda]) * (long long)(derecha - izquierda);
        long long denominador = datos[derecha] - datos[izquierda];
        int medio = izquierda + (int)(numerador / denominador);
        if (medio < izquierda) medio = izquierda;
        if (medio > derecha) medio = derecha;
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
    vector<long long> datos = generarDatosAdversarios(n);
    clock_t ordenInicio = clock();
    sort(datos.begin(), datos.end());
    clock_t ordenFin = clock();

    const long long clave = n - 2LL;
    int repeticiones = 1000000 / n;
    if (repeticiones < 1) repeticiones = 1;
    long long totalComparaciones = 0;
    volatile int resultado = -1;
    clock_t busquedaInicio = clock();
    for (int r = 0; r < repeticiones; ++r)
        resultado = busquedaInterpolacion(datos, clave, totalComparaciones);
    clock_t busquedaFin = clock();

    cout << fixed << setprecision(3)
         << "\n=== BUSQUEDA POR INTERPOLACION | VERSION IA ===\n"
         << "Elementos: " << n << '\n'
         << "Ordenamiento: " << 1000.0 * (ordenFin - ordenInicio) / CLOCKS_PER_SEC << " ms\n"
         << "Tiempo promedio de busqueda: " << 1000000.0 * (busquedaFin - busquedaInicio) / CLOCKS_PER_SEC / repeticiones << " us\n"
         << "Comparaciones promedio: " << (double)totalComparaciones / repeticiones << '\n'
         << "Resultado: " << (resultado < 0 ? "no encontrado" : "encontrado") << '\n';
    return 0;
}
