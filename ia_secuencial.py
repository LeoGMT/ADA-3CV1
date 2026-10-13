"""Busqueda secuencial con estructura profesional y medicion de alta resolucion."""
import random
from time import perf_counter_ns


def buscar(datos, objetivo):
    """Devuelve el indice de la primera coincidencia o -1 si no existe."""
    for indice, valor in enumerate(datos):
        if valor == objetivo:
            return indice
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

    print("\nBusqueda secuencial - version profesional")
    print("Elementos:", n, "| objetivo:", objetivo, "| indice:", posicion)
    print("Ordenamiento: {:.6f} ms".format(ordenamiento_ns / 1_000_000))
    print("Busqueda solamente: {:.6f} ms".format(busqueda_ns / 1_000_000))


if __name__ == "__main__":
    main()
