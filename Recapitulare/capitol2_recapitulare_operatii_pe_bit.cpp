#include <iostream>
using namespace std;
int main(){
int number=60;
number=number>>3;
cout<<number;
number=number<<3;
cout<<number<<endl;
long long name;
cout<<sizeof(name);//8bytes 
cout<<sizeof(number);//4bytes
return 0;
}

//pentru setarea porturilor 
//sa zicem ca vrem sa activam pinul PC3 din registrul PORTC
//PORTC=0b00001000
//PORTC=8;
//daca nu stim ce se afla in PORTC si vrem sa activam PC5
//1<<PC5 adica PORTC=PORTC | (1<<PC5)
//daca vrem sa stergem pinul 7 din PORTC vom recurge la PORTC&=~(1<<PC7)
//la fel si pentru verificarea daca vrem sa verificam daca un pin este activat sau nu exemplu portul 6 if((PORTC & 64)!=0)