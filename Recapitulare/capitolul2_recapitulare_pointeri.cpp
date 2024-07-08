//voi vorbi mai intai de tipuri de initializari
//#include <iostream>
//using namespace std;
//int main(){
  //  int x;
    //int y{5};
    //cout<<y;
    //int z={5};
    //int q{}; intitilaizare cu 0
//}

// in loc de cout putem sa folosim cerr << pentru a afisa datele (flushes the buffer)
//pointers and Syntax
//cateva exemple simple de pointeri
#include <string.h>
struct Person
    {
        char name[64];
        int age;
        char id[5];
    };
    void updatePerson(struct Person *p, int age, const char id[]) {
    p->age = age;
    
    strncpy(p->id, id, 4);
    p->id[4] = '\0'; 
    }

#include <iostream>
using namespace std;
int main(){
    //o variabila x
    int x = 10;
    int *px = &x;
    cout<<*px;//derefrence the thing pointied to by
    //poiteri sunt folositi atat pentru a nu mai repeta cod 
    //exemplu
    struct Person Mihai;
    updatePerson(&Mihai,100,"2002");
    
    //exemplu de pointer simplu
    //static vs dynamic memory alocation
    //dynamic memory allocation -memory alocated at run time
    //static memory memory alocated at compile time 
    //new and delete for a new we need a delete(memory leaks)
    //dynamicly alocate a integer variable 
    int*n=new int;//the new operator returns a memory adress
    //n was static alocated 
    *n=8;
    int *o;
    o=new int ;
    *o =2;
    int sum=*n +*o;

    //unamed is dynamicly alocated
    delete n;//free memory
    delete o;//free meory

    //dinamicly alocated array 
    int marime;//in cazul in care nu stim care va fi marimea vectorului  
    int *aptr;
    cout<<"Introduce marimea vectorului"<<endl;
    cin >> marime;
    aptr =new int[marime];

    for(int i=0;i< marime;i++){
        cout<<"elemetul"<<i<<':'<<endl;
        cin>>aptr[i];

    }
     //ararta rezultatele 
     for(int i=0;i<marime;i++){
        cout<<*(aptr+i)<<' '<<endl;
     }

     delete [] aptr;

}