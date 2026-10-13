"""Busqueda binaria iterativa con validacion y medicion en nanosegundos."""
import random
from time import perf_counter_ns


def buscar(datos, objetivo):
    """Busca objetivo en una secuencia ordenada y retorna el indice o -1."""
    izquierda, derecha = 0, len(datos) - 1
    while izquierda <= derecha:
        medio = izquierda + (derecha - izquierda) // 2
        valor = datos[medio]
        if valor == objetivo:
            return medio
        if valor < objetivo:
            izquierda = medio + 1
        else:
            derecha = medio - 1
    return -1


def main():
    try:
        n = int(input("Cantidad de elementos (1000, 10000, 100000, 1000000 o 10000000): "))
        if n < 1:
            raise ValueError
    except ValueError:
        print("Error: ingresa un entero positivo.")
        return

    generador = random.Random(20261012)
    datos = [10 * i + generador.randrange(10) for i in range(n)]
    generador.shuffle(datos)

    inicio = perf_counter_ns()
    datos.sort()
    ordenamiento_ns = perf_counter_ns() - inicio

    objetivo = datos[-1]
    inicio = perf_counter_ns()
    posicion = buscar(datos, objetivo)
    busqueda_ns = perf_counter_ns() - inicio

    print("\nBusqueda binaria - version profesional")
    print("Elementos:", n, "| objetivo:", objetivo, "| indice:", posicion)
    print("Ordenamiento: {:.6f} ms".format(ordenamiento_ns / 1_000_000))
    print("Busqueda solamente: {:.6f} ms".format(busqueda_ns / 1_000_000))


if __name__ == "__main__":
    main()
