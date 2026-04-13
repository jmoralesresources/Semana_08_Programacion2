#include <iostream>
#include <string>
using namespace std;

class Configuracion {
    string nombre;
    string version;
    static Configuracion* instancia;
    Configuracion() : nombre("App"), version("1.0") {} // contructor privado
public:
    static Configuracion& getInstance() {
        if (instancia == nullptr) instancia = new Configuracion();
        return *instancia;
    }
    string getNombre() const { return nombre; }
    string getVersion() const { return version; }
};
Configuracion* Configuracion::instancia = nullptr;

int main() {
    Configuracion& c = Configuracion::getInstance();
    cout << c.getNombre() << " " << c.getVersion() << endl;
    return 0;
}