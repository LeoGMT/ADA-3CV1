import random
import time


def buscar(datos, objetivo):
    inicio = 0
    fin = len(datos) - 1
    while inicio <= fin:
        medio = (inicio + fin) // 2
        if datos[medio] == objetivo:
            return medio
        elif datos[medio] < objetivo:
            inicio = medio + 1
        else:
            fin = medio - 1
    return -1


def main():
    n = int(input("Cantidad de elementos (1000, 10000, 100000, 1000000 o 10000000): "))
    if n < 1:
        print("La cantidad debe ser positiva.")
        return

    random.seed(2026)
    datos = [i * 10 + random.randint(0, 9) for i in range(n)]
    random.shuffle(datos)

    inicio = time.perf_counter()
    datos.sort()
    tiempo_ordenamiento = time.perf_counter() - inicio

    objetivo = datos[-1]
    inicio = time.perf_counter()
    posicion = buscar(datos, objetivo)
    tiempo_busqueda = time.perf_counter() - inicio

    print("\nBusqueda binaria basica")
    print("Posicion encontrada:", posicion)
    print("Tiempo de ordenamiento: {:.6f} segundos".format(tiempo_ordenamiento))
    print("Tiempo de busqueda: {:.9f} segundos".format(tiempo_busqueda))


if __name__ == "__main__":
    main()
