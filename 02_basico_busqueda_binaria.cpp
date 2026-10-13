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

    int buscado = 2 * n; // Ausente del conjunto.
    int repeticiones = 100000;
    long long comparaciones = 0;
    volatile int resultado = -1;
    clock_t inicioBusqueda = clock();
    for (int r = 0; r < repeticiones; r++) {
        int izquierda = 0, derecha = n - 1, posicion = -1;
        while (izquierda <= derecha) {
            int medio = izquierda + (derecha - izquierda) / 2;
            comparaciones++;
            if (numeros[medio] == buscado) { posicion = medio; break; }
            if (numeros[medio] < buscado) izquierda = medio + 1;
            else derecha = medio - 1;
        }
        resultado = posicion;
    }
    clock_t finBusqueda = clock();

    cout << fixed << setprecision(3);
    cout << "\n--- BUSQUEDA BINARIA BASICA ---\n";
    cout << "Elementos: " << n << "\n";
    cout << "Tiempo de ordenamiento: " << 1000.0 * (finOrden - inicioOrden) / CLOCKS_PER_SEC << " ms\n";
    cout << "Elemento buscado: " << buscado << " (ausente)\n";
    cout << "Comparaciones promedio: " << (double)comparaciones / repeticiones << "\n";
    cout << "Tiempo promedio de busqueda: " << 1000000.0 * (finBusqueda - inicioBusqueda) / CLOCKS_PER_SEC / repeticiones << " microsegundos\n";
    cout << "Resultado: " << (resultado == -1 ? "no encontrado" : "encontrado") << "\n";
    return 0;
}
