#include <iostream>
#include <vector>
//permite ncluderea unui fisier sursa in alt fiseir sursa 
// #define folosirea constantelor simbolice în programare
#define PI 3.14
#define LUNGIME 10

using namespace std;
//char 1byte
//unsigned char 1byte
//signed char 1byte
//int 2byte 
//unsigned int 2byte 
//long 4byte
//float 4byte 
//double 8byte 

int main() {
    //variabila este 
    const int  Lungime =10;
    //valori fixe care nu pot fi modificare in timpul executiei programului includ si cele cu define
    int i, j, k, l;
    //la aceste variabile se poate aduga si un idetificator  care sa prezinte durata de existenta si scopul acestora 
    //-register: variabile locale care pot fi stocate in registrii in loc de memoria ram ,pentru varabile care trebuie acesate rapid 
    //dimensiune max egala cu cea a registrului
    //-static: variabile create o singura data ,ramane in memorie cat ruleaza programul
    //-extern: permite referinte globale intre toate fisierele din program 

    cout << "Introduceți numărul de rânduri: ";
    cin >> k;
    cout << "Introduceți numărul de coloane: ";
    cin >> l;

    // Declarați o matrice folosind vectori
    vector<vector<int>> matrice(k, vector<int>(l));

    // Inițializați matricea
    for (i = 0; i < k; ++i) {
        for (j = 0; j < l; ++j) {
            matrice[i][j] = l;
        }
    }

    // Afișează matricea
    cout << "Matricea:" << endl;
    for (i = 0; i < k; ++i) {
        for (j = 0; j < l; ++j) {
            cout << matrice[i][j] << " ";
        }
        cout << endl;
    }

    // Afișează valoarea constantei LUNGIME
    cout << "Lungime: " << LUNGIME << endl;

    //initializare vector de elemente cu valori
    int initVec[5]={1,2,3,4,5};
    for(int i=0;i<5;i++){
        cout<<initVec[i]<<" ";
    }
    
    //opertatori specifici pentru operatiile pe biti operatorul complementar pe bit ~,si & sau | ,sau exclusiv ^ 
    //siftare la stanga << sau la  dreapta a bitilor

    //Instructiuni o portiune de cod care odata executata permite efectuarea unei actiuni de atribuire 
    //sizeof dimensiunea unei variabile 
    //& adresa variabilei
    //* pointer la variabila
    //operator ternar ? pentru a inlucui if-ul sau sa simplifice  if-ul ex: if(b<a)? c=5 : c=4;
    //avem intrctiuni de decizie if(expresie ) intructiune else intructiune
    //instructiuni de selectie precum ar fi switch(expresie){case c1:intructiune 1;break; case c2:instructiune 2;break; default:intructiune;break;}
    //instructiuni repetitive while/for/do while 
    //for(expresie1-evaluata la intrarea in bucla;expresie2-verificare conditie;expresie3-evaluata la sfarsit actulizeaza parametrii buclei)
    //do while este folosita cand se doreste executia cel putin o data a instructiunii din interior 
    //se executua intructiunea si apoi se evalueza expresia 
        return 0;
}
