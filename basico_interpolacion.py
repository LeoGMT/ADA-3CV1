import random
import time


def buscar(datos, objetivo):
    bajo = 0
    alto = len(datos) - 1
    while bajo <= alto and objetivo >= datos[bajo] and objetivo <= datos[alto]:
        if datos[bajo] == datos[alto]:
            if datos[bajo] == objetivo:
                return bajo
            return -1
        posicion = bajo + ((objetivo - datos[bajo]) * (alto - bajo)) // (datos[alto] - datos[bajo])
        if datos[posicion] == objetivo:
            return posicion
        if datos[posicion] < objetivo:
            bajo = posicion + 1
        else:
            alto = posicion - 1
    return -1


def main():
    n = int(input("Cantidad de elementos (1000, 10000, 100000, 1000000 o 10000000): "))
    if n < 1:
        print("La cantidad debe ser positiva.")
        return

    random.seed(2026)
    if n == 1:
        datos = [10**18]
    else:
        datos = [i * 10 + random.randint(0, 9) for i in range(n - 1)]
        datos.append(10**18)  # Valor extremo para que la interpolacion falle al estimar.
        random.shuffle(datos)

    inicio = time.perf_counter()
    datos.sort()
    tiempo_ordenamiento = time.perf_counter() - inicio

    objetivo = datos[-2] if n > 1 else datos[0]
    inicio = time.perf_counter()
    posicion = buscar(datos, objetivo)
    tiempo_busqueda = time.perf_counter() - inicio

    print("\nBusqueda por interpolacion basica (caso adversario)")
    print("Posicion encontrada:", posicion)
    print("Tiempo de ordenamiento: {:.6f} segundos".format(tiempo_ordenamiento))
    print("Tiempo de busqueda: {:.9f} segundos".format(tiempo_busqueda))


if __name__ == "__main__":
    main()
