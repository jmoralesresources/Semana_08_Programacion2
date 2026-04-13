#include <iostream>
using namespace std;

class Complejo {
    double real, imag;
public:
    Complejo(double r = 0, double i = 0) : real(r), imag(i) {}
    Complejo operator+(const Complejo& c) const {
        return Complejo(real + c.real, imag + c.imag);
    }
    Complejo operator-(const Complejo& c) const {
        return Complejo(real - c.real, imag - c.imag);
    }
    friend ostream& operator<<(ostream& out, const Complejo& c) {
        out << "(" << c.real << "," << c.imag << ")";
        return out;
    }
};

int main() {
    Complejo a(1, 2), b(3, 4);
    cout << a + b << endl;
    cout << a - b << endl;
    return 0;
}