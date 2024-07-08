#include <iostream>
using namespace std;

// Funcții în limbajul C++
void sayName(const char name[]) {
    cout << "Hello, my name is " << name << endl;
}

int main() {
    // Aici vom recapitula tablourile de date 
    // ex: float date[10] / tip nume_tablou_date[dimensiune]
    char name[3][10];
    int i = 0;

    // Citirea numelor de la tastatură
    cout << "Introduceți 3 nume (fiecare de maxim 9 caractere):" << endl;
    while (i < 3) {
        cin >> name[i];
        i++;
    }

    // Afișarea numelor introduse
    cout << "Numele introduse sunt:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << name[i] << " ";
    }
    cout << endl;

    // Pentru a inițializa datele unui vector vom folosi sintaxa de mai jos
    int number[3] = {1, 2, 3};
    for (i = 0; i < 3; i++) {
        cout << number[i] << " ";
    }
    cout << endl;

    // Tablouri unidimensionale care conțin tipul char
    // Pentru a marca sfârșitul unui șir de caractere după ultimul caracter se poate adăuga un octet '\0' numit terminator de șir
    char NumeSirNou[4] = {'r', 'a', '\0'};
    cout << NumeSirNou << endl;

    // Apelarea funcției sayName pentru fiecare nume
    for (i = 0; i < 3; i++) {
        sayName(name[i]);
    }

    return 0;
}
