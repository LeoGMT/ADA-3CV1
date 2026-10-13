#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cout << "Tamano del arreglo (1000, 10000, 100000, 1000000 o 10000000): ";
    cin >> n;
    if (n != 1000 && n != 10000 && n != 100000 && n != 1000000 && n != 10000000) {
        cout << "Tamano no valido.\n";
        return 1;
    }

    srand((unsigned)time(0));
    vector<long long> numeros(n);
    for (int i = 0; i < n - 1; i++) numeros[i] = i;
    numeros[n - 1] = 1000000000000000000LL;
    random_shuffle(numeros.begin(), numeros.end());

    clock_t inicioOrden = clock();
    sort(numeros.begin(), numeros.end());
    clock_t finOrden = clock();

    long long buscado = n - 2; // La estimacion cae repetidamente cerca del extremo izquierdo.
    int repeticiones = 1000000 / n;
    if (repeticiones < 1) repeticiones = 1;
    long long comparaciones = 0;
    volatile int resultado = -1;
    clock_t inicioBusqueda = clock();
    for (int r = 0; r < repeticiones; r++) {
        int izquierda = 0, derecha = n - 1, posicion = -1;
        while (izquierda <= derecha && buscado >= numeros[izquierda] && buscado <= numeros[derecha]) {
            if (numeros[izquierda] == numeros[derecha]) {
                comparaciones++;
                if (numeros[izquierda] == buscado) posicion = izquierda;
                break;
            }
            long long numerador = (buscado - numeros[izquierda]) * (derecha - izquierda);
            long long denominador = numeros[derecha] - numeros[izquierda];
            int medio = izquierda + (int)(numerador / denominador);
            if (medio < izquierda) medio = izquierda;
            if (medio > derecha) medio = derecha;
            comparaciones++;
            if (numeros[medio] == buscado) { posicion = medio; break; }
            if (numeros[medio] < buscado) izquierda = medio + 1;
            else derecha = medio - 1;
        }
        resultado = posicion;
    }
    clock_t finBusqueda = clock();

    cout << fixed << setprecision(3);
    cout << "\n--- BUSQUEDA POR INTERPOLACION BASICA ---\n";
    cout << "Elementos: " << n << "\n";
    cout << "Tiempo de ordenamiento: " << 1000.0 * (finOrden - inicioOrden) / CLOCKS_PER_SEC << " ms\n";
    cout << "Elemento buscado: " << buscado << " (arreglo adversario)\n";
    cout << "Comparaciones promedio: " << (double)comparaciones / repeticiones << "\n";
    cout << "Tiempo promedio de busqueda: " << 1000000.0 * (finBusqueda - inicioBusqueda) / CLOCKS_PER_SEC / repeticiones << " microsegundos\n";
    cout << "Resultado: " << (resultado == -1 ? "no encontrado" : "encontrado") << "\n";
    return 0;
}
