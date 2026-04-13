#include <iostream>
#include <memory>
using namespace std;

class BufferFacil {
    unique_ptr<char[]> datos;
    int tam;

public:
    BufferFacil(int n) : tam(n), datos(new char[n]) {
    }
    // Destructor, copia y asignación por defecto no sirven para recurso;
    // pero si usas unique_ptr, el default del destructor libera.
    // Copia hay que deshabilitar o implementar copia profunda del buffer.
};


int main() {
    BufferFacil b1(10);

    // BufferFacil b2 = b1; // falla

    // unique_ptr evita copias accidentales
    cout << "Fin del programa\n";

    return 0;
}