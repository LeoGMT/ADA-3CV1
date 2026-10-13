"""Busqueda hash: diccionario para caso promedio y una cubeta para colision extrema."""
import random
from time import perf_counter_ns


def construir_tabla(datos):
    """Construye un diccionario en el que cada clave es un numero del conjunto."""
    return dict.fromkeys(datos, True)


def buscar(tabla, objetivo):
    """Busca una clave en la tabla hash promedio de Python."""
    return objetivo in tabla


def construir_tabla_colisiones(datos):
    """Construye una tabla deliberadamente degenerada con una sola cubeta."""
    return [list(datos)]


def buscar_colision(tabla, objetivo):
    """Recorre la unica cubeta; permite medir el peor caso O(n) por colision."""
    for indice, valor in enumerate(tabla[0]):
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
    tabla = construir_tabla(datos)
    construccion_ns = perf_counter_ns() - inicio
    inicio = perf_counter_ns()
    encontrado = buscar(tabla, objetivo)
    busqueda_ns = perf_counter_ns() - inicio
    del tabla

    inicio = perf_counter_ns()
    tabla_colision = construir_tabla_colisiones(datos)
    construccion_colision_ns = perf_counter_ns() - inicio
    inicio = perf_counter_ns()
    posicion_colision = buscar_colision(tabla_colision, objetivo)
    busqueda_colision_ns = perf_counter_ns() - inicio

    print("\nBusqueda hash - version profesional")
    print("Elementos:", n, "| objetivo:", objetivo, "| encontrado:", encontrado)
    print("Ordenamiento: {:.6f} ms".format(ordenamiento_ns / 1_000_000))
    print("Construccion hash normal: {:.6f} ms".format(construccion_ns / 1_000_000))
    print("Busqueda hash normal: {:.6f} ms".format(busqueda_ns / 1_000_000))
    print("Construccion cubeta colisionada: {:.6f} ms".format(construccion_colision_ns / 1_000_000))
    print("Indice dentro de cubeta: ", posicion_colision)
    print("Busqueda con colisiones: {:.6f} ms".format(busqueda_colision_ns / 1_000_000))


if __name__ == "__main__":
    main()
