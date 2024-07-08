#include <iostream>
using namespace std;

//pointer functions care returneaza pointeri 
char *serch(char str[],char t){
 char *p=str; // p points to the first element of the array
 while(*p !='\0')
 {
    if(*p == t)
      return p;
    p++;
 }
 return nullptr;
}


void foo(int *p){
*p=88;
}

void foo2(int*& p,int*& q){
//we need to update the arguments therefore we need to pass by referance 
//*& the basic syntax
int* temp= p;
//refrenace paramaters that are refernacin pointers
//we use variables that hold inter adresses 

p=q;
q=temp; 
}
int main(){
    //pass pointers as arguments to functions 
    //pointer paramater pass by value or pass by referance 
 int x=9,y=2;
 int* q=&x;
 foo(q);
 cout<<x;
//example of passing the pointer by referance 
//anterior am folosti un pas in plus care se foloseste pentru derefrence pointer 
 int* xptr=&x;
 //x pointer poits to x and y pointer points to y 
 int* yptr=&y;

cout << *xptr<<"- adresa -"<<xptr<<endl;
cout<< *yptr<<"- adresa -"<<yptr<<endl;

foo2(xptr,yptr);

cout << *xptr<<"- adresa -"<<xptr<<endl;
cout<< *yptr<<"- adresa -"<<yptr<<endl;

//the pointers are now swaped xptr points to y and yptr points to x
//so the values have swaped 

 char name[]="String";
 char t='t';
  //returning pointers from functions cum se face 
  char* ser= serch(name,t);
  
if(*ser == 't'){
 cout<<"found"<<endl;
}else{
    cout<<"not found "<<t;
}
return 0;
}