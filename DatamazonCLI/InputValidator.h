#pragma once
#include <iostream>
#include <string>
#include <limits>

using namespace std;

class InputValidator {
public:
    template <typename T>
    static T readNumeric(string prompt) {
        T value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                return value;
            } else {
                cout << "Entrada invalida. Por favor, ingrese un valor numerico valido." << endl;
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            }
        }
    }
};
