#include <iostream>
#include <cstring>
using namespace std;

class Student {
    private:
        int lungimeNume;
        int lungimePrenume;
        char* Name;
        char* Prename;
        int Age;
    public:
        Student(int ln, int lp) : lungimeNume(ln), lungimePrenume(lp) {
            Name = new char[lungimeNume];
            Prename = new char[lungimePrenume];
        }
//constrctorul de mai sus ne arata si alte metode prin care putem initializa valorile sale
//Student(int ln,int lp): initilaizarea celor 2 variabile 
//alocarea dinamica a celor doua atribute ale clasei 
        ~Student() {
            delete[] Name;
            delete[] Prename;
        }
        //si sa nu uitam dealocarea prin apelarea decosntructorului 
        //pentru a evita scurgerile de memorie 


        void setName(const char name[]) {
            strncpy(this->Name, name, lungimeNume - 1);
            this->Name[lungimeNume - 1] = '\0'; // Ensure null termination
        }
        
        const char* getName() const {
            return this->Name;
        }
        
        void setPrename(const char prename[]) {
            strncpy(this->Prename, prename, lungimePrenume - 1);
            this->Prename[lungimePrenume - 1] = '\0'; // Ensure null termination
        }

        const char* getPrename() const {
            return this->Prename;
        }

        void setAge(int age) {
            this->Age = age;
        }

        int getAge() const {
            return this->Age;
        }
};

//urmatoarele doua clase vor reprezenta abitatea polimorfismului si
//la ce se folosesc functiile virtuale 
//clasa de baza 
 class Squere {
    private: int x;
    public: Squere(int _x):x(_x){};
    int setX(int _x){x=_x;};
    int getX()const{return x;};
    virtual ~Squere(){};
    virtual void print() const {cout<< "Squere!\n";};
    //folosim virtual pentru a putea suprascrie acea functie in clasele derivate
    //the binding changhes from static to dinamic 
    //trebuie sa fie pusa doar in clasa de baza 
    //overriding 
 };

 //clasa derivata 
class Rectange:public Squere{
    private:
    int y;

    public:
    Rectange(int _x,int _y):Squere(_x){y=_y;}
    virtual ~Rectange(){};
    void setY(int _y){ y=_y;}
    int getY(){return y;}
    void print() const {cout<<"rectangle";};
};

void foo(const Squere& s){
    cout<<s.getX();
};//trebuie sa folosim referinte sau pointeri pentru a folosi acesata suprascriere dinamica 
//is a squre
class Foo :public Squere{
public:
 Squere::Squere;//mosteneste contructorul de la clasa de baza Squere 
 void print()const {cout<<"foo";};
 virtual ~Foo(){};//trebuie sa declaram destructorii pentru ficare dintre clase pentru a putea dealoca memoria la final
 //altfel vom primi o erroare 
};

int main() {
    Student student(50, 50); 
    student.setName("John");
    student.setPrename("Doe");
    student.setAge(21);

    cout << "Name: " << student.getName() << endl;
    cout << "Prename: " << student.getPrename() << endl;
    cout << "Age: " << student.getAge() << endl;
    //polimorfism
    Squere s(4);
    Rectange r(2,4);
    foo(r);

    Squere *sptr=&r;
    sptr->print();
    //cream un vector de obiecte de tip Squere pointers care va aloca dinamic adrese de obiecte noi alocate cu new dinamic memory alocation
    Squere* squres[]={new Squere(3),new Rectange(1,2),new Foo(1)};

    for(Squere* s :squres){
        s->print();
    }
    for (Squere* s:squres){
        delete s;
    }
    return 0;
}
