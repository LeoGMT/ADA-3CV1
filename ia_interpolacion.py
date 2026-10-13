"""Busqueda por interpolacion defensiva para secuencias numericas ordenadas."""
import random
from time import perf_counter_ns


def buscar(datos, objetivo):
    """Retorna el indice del objetivo o -1; valida limites y division por cero."""
    if not datos:
        return -1
    bajo, alto = 0, len(datos) - 1
    while bajo <= alto and datos[bajo] <= objetivo <= datos[alto]:
        valor_bajo, valor_alto = datos[bajo], datos[alto]
        if valor_bajo == valor_alto:
            return bajo if valor_bajo == objetivo else -1
        numerador = (objetivo - valor_bajo) * (alto - bajo)
        posicion = bajo + numerador // (valor_alto - valor_bajo)
        # Protege la busqueda ante redondeos o datos extremos.
        posicion = max(bajo, min(posicion, alto))
        valor = datos[posicion]
        if valor == objetivo:
            return posicion
        if valor < objetivo:
            bajo = posicion + 1
        else:
            alto = posicion - 1
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
    if n == 1:
        datos = [10**18]
    else:
        datos = [10 * i + generador.randrange(10) for i in range(n - 1)]
        datos.append(10**18)
        generador.shuffle(datos)

    inicio = perf_counter_ns()
    datos.sort()
    ordenamiento_ns = perf_counter_ns() - inicio

    objetivo = datos[-2] if n > 1 else datos[0]
    inicio = perf_counter_ns()
    posicion = buscar(datos, objetivo)
    busqueda_ns = perf_counter_ns() - inicio

    print("\nBusqueda por interpolacion - version profesional, distribucion adversaria")
    print("Elementos:", n, "| objetivo:", objetivo, "| indice:", posicion)
    print("Ordenamiento: {:.6f} ms".format(ordenamiento_ns / 1_000_000))
    print("Busqueda solamente: {:.6f} ms".format(busqueda_ns / 1_000_000))


if __name__ == "__main__":
    main()
