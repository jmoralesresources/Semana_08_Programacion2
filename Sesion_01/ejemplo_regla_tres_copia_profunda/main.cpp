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
        datos = nullptr;
    }
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
};

int main() {
    Buffer b1(10);
    Buffer b2 = b1;
    Buffer b3(5);
    b3 = b1;
    return 0;
}