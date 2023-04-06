#include "Animal.hpp"

Animal::Animal(int iage, string iname, string itype){
    age = iage;
    name = iname;
    type = itype;
}

void Animal::toString(){
    //cout<<"Basic unit of our Zoo application, refers to multicelluar organism whose cells do not have cell walls. This is an abstract class!"<<endl;
    cout<<"The specie is: "<<type<<endl;
    cout<<"The animal name is: "<<name<<endl;
    cout<<"The animal age is: "<<age<<endl;
}

string Animal::getType(){
    return this->type;  
}

int Animal::getAge(){
    return this->age;
}