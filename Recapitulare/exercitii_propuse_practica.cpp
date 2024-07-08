//inversiunea  a doua numere 
//ex 1
#include <iostream>
using namespace std;
//ex 2 functie care returneaza 1 daca numarul este par sau 0 daca este impar
int par_impar(int a){
if(a%2==0){
    return 1;
}
else return 0;
};

//exercitiul 3
int comparare(int a,int b,int c){
if(a > b && a > c){
    return a;
}else if(b >a && b > c){
    return b;
}
else {return c;
}
}
//varianta cu template acum functia noastra poate functiona 
//cu orice tip de data pe care il specificam 
template<typename T>
T comparare2(T a,T b,T c){
    if(a > b && a > c){
    return a;
}else if(b >a && b > c){
    return b;
}
else {return c;}
}
//exercitiul 4
template <typename T, int N>
T minicalculator() {
    T elemente[N];
    T rezultat;
    string comanda;

    // Get the elements from the user
    for(int i = 0; i < N; i++) {
        cout << "Give me element " << i+1 << ": ";
        cin >> elemente[i];
    }

    // Initialize the result with the first element
    rezultat = elemente[0];

    // Process the operations
    for(int i = 1; i < N; i++) {
        cout << "Give me operation for element " << i+1 << ": ";
        cin >> comanda;

        if (comanda == "adunare") {
            rezultat += elemente[i];
        } else if (comanda == "scadere") {
            rezultat -= elemente[i];
        } else if (comanda == "inmultire") {
            rezultat *= elemente[i];
        } else if (comanda == "impartire") {
            if (elemente[i] != 0) {
                rezultat /= elemente[i];
            } else {
                cout << "Error: Division by zero" << endl;
                return rezultat;
            }
        } else {
            cout << "Invalid operation" << endl;
            return rezultat;
        }
    }

    return rezultat;
}

//exercitiul 5
int getBitState(int numarul,int pozitia){
return (numarul>> pozitia) & 1;
//adica daca avem 20
//care este in binar 0001_0100
//vrem sa aflam starea bitului de pe poz 2
//vom face 20 >> 2 care ne da 0000_0101
//daca facem si cu lsb va rezulta 1 
}
//acum voi implementa aceeasi functie cu template 
//voi da mai intai un exemlu generic pentru template 
template <typename T>
void Print(T value){
    std::cout<<value<<endl;
}
//functie generica pentru afisare
//putem sa folosim templates pentru clase de asemenea 
//exemplu daca vrem sa avem o clasa care are un array caruia nu ii stim marimiea cand
//clasa este creata acesta va fi decisa ulterior 
template<typename T,int N>
class Array
{
private: 
T m_array[N];
public:
int GetSize() const {return N;}
};
//daca vrem sa apelam acesta clasa vom folosi Array<int,5> array
int main() {
    Print<int>(5);
    int a, b, invers_a, invers_b;
    int* a_holder = new int;
    int* b_holder = new int;
    
    cout << "Introduceti doua numere de la tastatura" << endl;
    cin >> a;
    cin >> b;
    //ex2 functie par rezultat
    cout<<par_impar(a)<<endl;
    
    invers_a = 0;
    invers_b = 0;
    *a_holder = a;
    *b_holder = b;
    
    while (*a_holder != 0 || *b_holder != 0) {
        if (*a_holder != 0) {
            int temp_a = *a_holder % 10;
            invers_a = invers_a * 10 + temp_a;
            *a_holder = *a_holder / 10;
        }
        if (*b_holder != 0) {
            int temp_b = *b_holder % 10;
            invers_b = invers_b * 10 + temp_b;
            *b_holder = *b_holder / 10;
        }
    }
    
    delete a_holder;
    delete b_holder;
    
    cout << "Numerele inversate sunt: " << invers_a << " " << invers_b << endl;
    cout << minicalculator<int, 3>() << endl;
    cout << minicalculator<double, 3>() << endl;
    return 0;
}
