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

int hashSimple(int valor, int capacidad) {
    return (int)(((long long)valor * 31 + 7) % capacidad);
}

int main() {
    int n;
    cout << "Tamano del arreglo (1000, 10000, 100000, 1000000 o 10000000): ";
    cin >> n;
    if (n != 1000 && n != 10000 && n != 100000 && n != 1000000 && n != 10000000) {
        cout << "Tamano no valido.\n";
        return 1;
    }
    srand((unsigned)time(0));
    vector<int> numeros(n);
    for (int i = 0; i < n; i++) numeros[i] = numeroAleatorio(2 * n);
    clock_t inicioOrden = clock();
    sort(numeros.begin(), numeros.end());
    clock_t finOrden = clock();

    int capacidad = 2 * n + 1;
    vector<int> tabla(capacidad, -1);
    clock_t inicioConstruccion = clock();
    for (int i = 0; i < n; i++) {
        int lugar = hashSimple(numeros[i], capacidad);
        while (tabla[lugar] != -1 && tabla[lugar] != numeros[i]) lugar = (lugar + 1) % capacidad;
        tabla[lugar] = numeros[i];
    }
    clock_t finConstruccion = clock();

    int buscado = 2 * n;
    int repeticiones = 100000;
    long long pasos = 0;
    volatile int resultado = 0;
    clock_t inicioBusqueda = clock();
    for (int r = 0; r < repeticiones; r++) {
        int lugar = hashSimple(buscado, capacidad);
        bool encontrado = false;
        while (tabla[lugar] != -1) {
            pasos++;
            if (tabla[lugar] == buscado) { encontrado = true; break; }
            lugar = (lugar + 1) % capacidad;
        }
        pasos++;
        resultado = encontrado ? 1 : 0;
    }
    clock_t finBusqueda = clock();

    // Peor caso de colisiones: todas las claves se alojan en una misma cubeta.
    vector<int> cubeta(numeros);
    int repPeor = 1000000 / n;
    if (repPeor < 1) repPeor = 1;
    long long pasosPeor = 0;
    clock_t inicioPeor = clock();
    for (int r = 0; r < repPeor; r++) {
        bool encontrado = false;
        for (int i = 0; i < (int)cubeta.size(); i++) {
            pasosPeor++;
            if (cubeta[i] == buscado) { encontrado = true; break; }
        }
        resultado = encontrado ? 1 : 0;
    }
    clock_t finPeor = clock();

    cout << fixed << setprecision(3);
    cout << "\n--- TABLA HASH BASICA ---\n";
    cout << "Elementos: " << n << "\n";
    cout << "Ordenamiento: " << 1000.0 * (finOrden - inicioOrden) / CLOCKS_PER_SEC << " ms\n";
    cout << "Construccion hash: " << 1000.0 * (finConstruccion - inicioConstruccion) / CLOCKS_PER_SEC << " ms\n";
    cout << "Busqueda hash promedio: " << 1000000.0 * (finBusqueda - inicioBusqueda) / CLOCKS_PER_SEC / repeticiones << " us; inspecciones promedio: " << (double)pasos / repeticiones << "\n";
    cout << "Busqueda con colision total: " << 1000000.0 * (finPeor - inicioPeor) / CLOCKS_PER_SEC / repPeor << " us; inspecciones promedio: " << (double)pasosPeor / repPeor << "\n";
    return 0;
}
