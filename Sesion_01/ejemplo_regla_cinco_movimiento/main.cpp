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

int main() {
    Buffer b1(10);

    Buffer b2 = move(b1); // movimiento

    Buffer b3(5);
    b3 = move(b2);        // asignación por movimiento

    return 0;
}