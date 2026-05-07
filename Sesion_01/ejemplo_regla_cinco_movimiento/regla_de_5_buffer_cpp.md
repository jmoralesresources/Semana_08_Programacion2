# Regla de 5 en C++: explicación paso a paso con la clase `Buffer`

## 1. ¿Qué es la Regla de 5?

La **Regla de 5** en C++ dice que si una clase administra un recurso dinámico, como memoria reservada con `new`, normalmente debe definir estas cinco funciones especiales:

| Función | Propósito |
|---|---|
| Destructor | Liberar el recurso dinámico |
| Constructor de copia | Crear una copia independiente del objeto |
| Operador de asignación por copia | Copiar correctamente un objeto ya existente |
| Constructor de movimiento | Transferir el recurso desde un objeto temporal |
| Operador de asignación por movimiento | Mover el recurso hacia un objeto ya existente |

En este caso, la clase `Buffer` administra memoria dinámica mediante un puntero:

```cpp
char* datos;
```

Por eso es necesario controlar cuidadosamente cómo se copia, se mueve y se destruye el objeto.

---

# 2. Código base

```cpp
#include <iostream>
#include <cstring>
using namespace std;

class Buffer {
    char* datos;
    int tam;

public:
    Buffer(int n) : tam(n) {
        datos = new char[n];
    }

    ~Buffer() {
        delete[] datos;
    }

    // Copia
    Buffer(const Buffer& other) : tam(other.tam) {
        datos = new char[tam];
        memcpy(datos, other.datos, tam);
    }

    Buffer& operator=(const Buffer& other) {

        if (this == &other) return *this;

        delete[] datos;
        tam = other.tam;
        datos = new char[tam];
        memcpy(datos, other.datos, tam);

        return *this;
    }

    // Movimiento
    Buffer(Buffer&& other) noexcept : datos(other.datos), tam(other.tam) {
        other.datos = nullptr;
        other.tam = 0;
    }

    Buffer& operator=(Buffer&& other) noexcept {

        if (this == &other) return *this;

        delete[] datos;

        datos = other.datos;
        tam = other.tam;

        other.datos = nullptr;
        other.tam = 0;

        return *this;
    }
};
```

---

# 3. Atributos de la clase

```cpp
char* datos;
int tam;
```

## Explicación

La clase tiene dos atributos:

| Atributo | Significado |
|---|---|
| `datos` | Puntero a un arreglo dinámico de caracteres |
| `tam` | Tamaño del arreglo |

El atributo importante es `datos`, porque apunta a memoria creada con `new[]`.

```cpp
datos = new char[n];
```

Cuando una clase usa `new`, también debe usar `delete` para liberar memoria.

---

# 4. Constructor normal

```cpp
Buffer(int n) : tam(n) {
    datos = new char[n];
}
```

## ¿Qué hace?

Este constructor crea un objeto `Buffer` con capacidad para `n` caracteres.

Paso a paso:

1. Recibe un tamaño `n`.
2. Guarda ese tamaño en `tam`.
3. Reserva memoria dinámica con `new char[n]`.
4. Guarda la dirección de esa memoria en `datos`.

Ejemplo:

```cpp
Buffer b1(10);
```

Esto crea un objeto con un arreglo dinámico de 10 caracteres.

---

# 5. Destructor

```cpp
~Buffer() {
    delete[] datos;
}
```

## ¿Qué hace?

El destructor se ejecuta automáticamente cuando el objeto deja de existir.

Su función es liberar la memoria dinámica que fue reservada con `new[]`.

Sin este destructor, habría una fuga de memoria.

## Ejemplo

```cpp
{
    Buffer b1(10);
} 
// Aquí se llama automáticamente al destructor
```

Cuando `b1` sale del bloque, se ejecuta:

```cpp
delete[] datos;
```

---

# 6. Constructor de copia

```cpp
Buffer(const Buffer& other) : tam(other.tam) {
    datos = new char[tam];
    memcpy(datos, other.datos, tam);
}
```

## ¿Qué hace?

Crea un nuevo objeto copiando los datos de otro objeto `Buffer`.

Ejemplo:

```cpp
Buffer b1(10);
Buffer b2 = b1;
```

Aquí se llama al constructor de copia.

## Paso a paso

1. Recibe otro objeto llamado `other`.
2. Copia el tamaño:

```cpp
tam = other.tam;
```

3. Reserva nueva memoria para el objeto actual:

```cpp
datos = new char[tam];
```

4. Copia el contenido del arreglo de `other` hacia el arreglo del nuevo objeto:

```cpp
memcpy(datos, other.datos, tam);
```

## ¿Por qué no basta con copiar el puntero?

Porque si se hiciera una copia superficial, ambos objetos apuntarían a la misma memoria.

Ejemplo del problema:

```cpp
datos = other.datos;
```

Eso sería peligroso porque dos objetos intentarían liberar la misma memoria con `delete[]`.

Eso puede provocar error en tiempo de ejecución.

---

# 7. Operador de asignación por copia

```cpp
Buffer& operator=(const Buffer& other) {

    if (this == &other) return *this;

    delete[] datos;
    tam = other.tam;
    datos = new char[tam];
    memcpy(datos, other.datos, tam);

    return *this;
}
```

## ¿Cuándo se usa?

Se usa cuando un objeto ya existe y se le asigna otro objeto.

Ejemplo:

```cpp
Buffer b1(10);
Buffer b2(5);

b2 = b1;
```

Aquí no se está creando `b2`, porque `b2` ya existe.  
Por eso se llama al operador de asignación por copia.

## Paso a paso

### Paso 1: Verificar autoasignación

```cpp
if (this == &other) return *this;
```

Esto evita problemas si el objeto se asigna a sí mismo.

Ejemplo:

```cpp
b1 = b1;
```

Sin esta validación, el objeto podría borrar sus propios datos antes de copiarlos.

---

### Paso 2: Liberar la memoria anterior

```cpp
delete[] datos;
```

Como el objeto ya tenía memoria reservada, primero se libera para evitar fugas de memoria.

---

### Paso 3: Copiar el tamaño

```cpp
tam = other.tam;
```

El objeto actual toma el mismo tamaño del objeto que se está copiando.

---

### Paso 4: Reservar nueva memoria

```cpp
datos = new char[tam];
```

Se reserva memoria nueva e independiente.

---

### Paso 5: Copiar los datos

```cpp
memcpy(datos, other.datos, tam);
```

Se copian los datos desde `other` hacia el objeto actual.

---

### Paso 6: Retornar el objeto actual

```cpp
return *this;
```

Esto permite asignaciones encadenadas:

```cpp
a = b = c;
```

---

# 8. Constructor de movimiento

```cpp
Buffer(Buffer&& other) noexcept : datos(other.datos), tam(other.tam) {
    other.datos = nullptr;
    other.tam = 0;
}
```

## ¿Qué hace?

El constructor de movimiento crea un nuevo objeto tomando los recursos de otro objeto temporal.

Ejemplo:

```cpp
Buffer crearBuffer() {
    Buffer temp(10);
    return temp;
}

Buffer b1 = crearBuffer();
```

El objeto temporal puede ser movido en lugar de copiado.

## Paso a paso

### Paso 1: Tomar el puntero del otro objeto

```cpp
datos(other.datos)
```

El nuevo objeto recibe directamente la dirección de memoria que tenía `other`.

---

### Paso 2: Tomar el tamaño

```cpp
tam(other.tam)
```

El nuevo objeto recibe el tamaño del buffer.

---

### Paso 3: Anular el objeto original

```cpp
other.datos = nullptr;
other.tam = 0;
```

Esto es muy importante.

Después del movimiento, `other` ya no debe seguir apuntando a la memoria, porque esa memoria ahora pertenece al nuevo objeto.

Si no se pone `other.datos = nullptr`, ambos objetos podrían intentar liberar la misma memoria.

---

### Paso 4: Uso de `noexcept`

```cpp
noexcept
```

Indica que esta operación no debería lanzar excepciones.

Esto es recomendable en constructores de movimiento porque permite que contenedores como `vector` usen movimiento de forma más eficiente.

---

# 9. Operador de asignación por movimiento

```cpp
Buffer& operator=(Buffer&& other) noexcept {

    if (this == &other) return *this;

    delete[] datos;

    datos = other.datos;
    tam = other.tam;

    other.datos = nullptr;
    other.tam = 0;

    return *this;
}
```

## ¿Cuándo se usa?

Se usa cuando un objeto ya existente recibe los recursos de un objeto temporal.

Ejemplo:

```cpp
Buffer b1(10);
Buffer b2(5);

b2 = std::move(b1);
```

Aquí se llama al operador de asignación por movimiento.

---

## Paso a paso

### Paso 1: Verificar autoasignación

```cpp
if (this == &other) return *this;
```

Evita problemas si accidentalmente se intenta mover el objeto hacia sí mismo.

---

### Paso 2: Liberar la memoria actual

```cpp
delete[] datos;
```

Como el objeto ya tenía memoria, primero debe liberarla.

---

### Paso 3: Tomar el puntero del otro objeto

```cpp
datos = other.datos;
```

El objeto actual toma la memoria de `other`.

---

### Paso 4: Tomar el tamaño

```cpp
tam = other.tam;
```

El objeto actual toma el tamaño de `other`.

---

### Paso 5: Dejar el otro objeto vacío

```cpp
other.datos = nullptr;
other.tam = 0;
```

Esto evita que el objeto movido libere una memoria que ya no le pertenece.

---

### Paso 6: Retornar el objeto actual

```cpp
return *this;
```

Permite asignaciones encadenadas.

---

# 10. Diferencia entre copia y movimiento

| Operación | Qué hace | Costo |
|---|---|---|
| Copia | Crea nueva memoria y copia los datos | Más costosa |
| Movimiento | Transfiere el puntero sin copiar los datos | Más eficiente |

## Copia

```cpp
Buffer b1(100);
Buffer b2 = b1;
```

`b2` tendrá su propia memoria y una copia de los datos de `b1`.

---

## Movimiento

```cpp
Buffer b1(100);
Buffer b2 = std::move(b1);
```

`b2` toma la memoria de `b1`.

Después de eso, `b1` queda vacío:

```cpp
b1.datos = nullptr;
b1.tam = 0;
```

---

# 11. ¿Por qué esta clase necesita la Regla de 5?

Porque administra memoria dinámica manualmente.

```cpp
datos = new char[n];
```

Si no se implementan correctamente copia, asignación, movimiento y destrucción, pueden ocurrir errores como:

- Fugas de memoria.
- Doble liberación de memoria.
- Punteros colgantes.
- Copias superficiales incorrectas.
- Errores al destruir objetos.

---

# 12. Versión comentada del código

```cpp
#include <iostream>
#include <cstring>
using namespace std;

class Buffer {
    char* datos; // Puntero a memoria dinámica
    int tam;     // Tamaño del buffer

public:
    // Constructor normal
    Buffer(int n) : tam(n) {
        datos = new char[n]; // Reserva memoria dinámica
    }

    // Destructor
    ~Buffer() {
        delete[] datos; // Libera la memoria reservada
    }

    // Constructor de copia
    Buffer(const Buffer& other) : tam(other.tam) {
        datos = new char[tam];              // Reserva nueva memoria
        memcpy(datos, other.datos, tam);    // Copia los datos
    }

    // Operador de asignación por copia
    Buffer& operator=(const Buffer& other) {

        // Evita problemas si se hace b1 = b1
        if (this == &other) return *this;

        delete[] datos;                     // Libera memoria anterior
        tam = other.tam;                    // Copia el tamaño
        datos = new char[tam];              // Reserva nueva memoria
        memcpy(datos, other.datos, tam);    // Copia los datos

        return *this;                       // Retorna el objeto actual
    }

    // Constructor de movimiento
    Buffer(Buffer&& other) noexcept 
        : datos(other.datos), tam(other.tam) {

        // El recurso pasa al nuevo objeto
        // El objeto original queda vacío
        other.datos = nullptr;
        other.tam = 0;
    }

    // Operador de asignación por movimiento
    Buffer& operator=(Buffer&& other) noexcept {

        // Evita autoasignación
        if (this == &other) return *this;

        delete[] datos;       // Libera la memoria actual

        datos = other.datos;  // Toma el recurso del otro objeto
        tam = other.tam;      // Toma el tamaño

        other.datos = nullptr; // El otro objeto ya no posee el recurso
        other.tam = 0;

        return *this;
    }
};
```

---

# 13. Resumen didáctico

La clase `Buffer` cumple la **Regla de 5** porque define:

```cpp
~Buffer();
Buffer(const Buffer& other);
Buffer& operator=(const Buffer& other);
Buffer(Buffer&& other) noexcept;
Buffer& operator=(Buffer&& other) noexcept;
```

En palabras simples:

| Función | Explicación sencilla |
|---|---|
| Destructor | Borra la memoria cuando el objeto muere |
| Constructor de copia | Crea una copia nueva e independiente |
| Asignación por copia | Reemplaza el contenido actual por una copia |
| Constructor de movimiento | Roba el recurso de un objeto temporal |
| Asignación por movimiento | Libera lo actual y toma el recurso de otro objeto |

---

# 14. Frase clave para clase

La **Regla de 5** se usa cuando una clase administra recursos dinámicos.  
Su objetivo es evitar errores de memoria al copiar, asignar, mover o destruir objetos.

