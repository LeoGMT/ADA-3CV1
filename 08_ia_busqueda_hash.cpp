// Solucion estructurada propuesta por IA: tabla hash con direccionamiento abierto.
// Compatible con C++98 y Dev-C++ clasico. Se muestra busqueda normal y colision total.
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
    srand(141421u + (unsigned)n);
    for (int i = 0; i < n; ++i) datos[i] = numeroAleatorio(2 * n);
    return datos;
}

int funcionHash(int clave, int capacidad) {
    return (int)(((long long)clave * 31 + 7) % capacidad);
}

void insertar(vector<int>& tabla, int clave) {
    int indice = funcionHash(clave, (int)tabla.size());
    while (tabla[indice] != -1 && tabla[indice] != clave)
        indice = (indice + 1) % (int)tabla.size();
    tabla[indice] = clave;
}

bool contiene(const vector<int>& tabla, int clave, long long& inspecciones) {
    int indice = funcionHash(clave, (int)tabla.size());
    while (tabla[indice] != -1) {
        ++inspecciones;
        if (tabla[indice] == clave) return true;
        indice = (indice + 1) % (int)tabla.size();
    }
    ++inspecciones; // Se cuenta la casilla vacia que termina la busqueda.
    return false;
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

    vector<int> tabla(2 * n + 1, -1);
    clock_t construccionInicio = clock();
    for (int i = 0; i < n; ++i) insertar(tabla, datos[i]);
    clock_t construccionFin = clock();

    const int clave = 2 * n;
    const int repeticiones = 100000;
    long long inspecciones = 0;
    volatile int resultado = 0;
    clock_t busquedaInicio = clock();
    for (int r = 0; r < repeticiones; ++r)
        resultado = contiene(tabla, clave, inspecciones) ? 1 : 0;
    clock_t busquedaFin = clock();

    // Representa una tabla de encadenamiento donde el hash adversario manda todo a una cubeta.
    vector<int> cubeta(datos);
    int repPeor = 1000000 / n;
    if (repPeor < 1) repPeor = 1;
    long long pasosColision = 0;
    clock_t colisionInicio = clock();
    for (int r = 0; r < repPeor; ++r) {
        bool encontrado = false;
        for (int i = 0; i < (int)cubeta.size(); ++i) {
            ++pasosColision;
            if (cubeta[i] == clave) { encontrado = true; break; }
        }
        resultado = encontrado ? 1 : 0;
    }
    clock_t colisionFin = clock();

    cout << fixed << setprecision(3)
         << "\n=== TABLA HASH | VERSION IA ===\n"
         << "Elementos: " << n << '\n'
         << "Ordenamiento previo: " << 1000.0 * (ordenFin - ordenInicio) / CLOCKS_PER_SEC << " ms\n"
         << "Construccion hash: " << 1000.0 * (construccionFin - construccionInicio) / CLOCKS_PER_SEC << " ms\n"
         << "Busqueda hash normal: " << 1000000.0 * (busquedaFin - busquedaInicio) / CLOCKS_PER_SEC / repeticiones << " us; inspecciones promedio: " << (double)inspecciones / repeticiones << '\n'
         << "Busqueda con colision total: " << 1000000.0 * (colisionFin - colisionInicio) / CLOCKS_PER_SEC / repPeor << " us; inspecciones promedio: " << (double)pasosColision / repPeor << '\n';
    return 0;
}
