#include <iostream>
using namespace std;

class CalculadoraLegacy {
public:
    int calcular(int a, int b) { return a + b; }
};

class ICalculadoraModerno {
public:
    virtual double calcular(double a, double b) = 0;
    virtual ~ICalculadoraModerno() = default;
};

class AdapterCalculadora : public ICalculadoraModerno {
    CalculadoraLegacy legacy;
public:
    double calcular(double a, double b) override {
        return legacy.calcular(static_cast<int>(a), static_cast<int>(b));
    }
};

int main() {
    AdapterCalculadora ad;
    cout << ad.calcular(2.5, 3.7) << endl;
    return 0;
}