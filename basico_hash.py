import random
import time


def construir_tabla(datos):
    tabla = {}
    for valor in datos:
        tabla[valor] = True
    return tabla


def buscar(tabla, objetivo):
    if objetivo in tabla:
        return True
    return False


def construir_tabla_colisiones(datos):
    # Simula una tabla de una sola cubeta: todas las claves colisionan.
    return [list(datos)]


def buscar_colision(tabla, objetivo):
    for i in range(len(tabla[0])):
        if tabla[0][i] == objetivo:
            return i
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
    tabla = construir_tabla(datos)
    tiempo_construccion = time.perf_counter() - inicio
    inicio = time.perf_counter()
    encontrado = buscar(tabla, objetivo)
    tiempo_busqueda = time.perf_counter() - inicio

    inicio = time.perf_counter()
    tabla_colision = construir_tabla_colisiones(datos)
    tiempo_construccion_colision = time.perf_counter() - inicio
    inicio = time.perf_counter()
    posicion = buscar_colision(tabla_colision, objetivo)
    tiempo_busqueda_colision = time.perf_counter() - inicio

    print("\nBusqueda hash basica")
    print("Encontrado en tabla normal:", encontrado)
    print("Tiempo de ordenamiento: {:.6f} segundos".format(tiempo_ordenamiento))
    print("Tiempo de construccion hash: {:.6f} segundos".format(tiempo_construccion))
    print("Tiempo de busqueda hash normal: {:.9f} segundos".format(tiempo_busqueda))
    print("Tiempo de construccion hash con colisiones: {:.6f} segundos".format(tiempo_construccion_colision))
    print("Posicion en la cubeta con colisiones:", posicion)
    print("Tiempo de busqueda con colisiones: {:.9f} segundos".format(tiempo_busqueda_colision))


if __name__ == "__main__":
    main()
