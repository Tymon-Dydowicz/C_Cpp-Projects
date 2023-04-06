#include "Carnivore.hpp"

Carnivore::Carnivore(int iage, string iname, string type, string imeat) : Animal(iage, iname, type){
    favMeat = imeat;
}

void Carnivore::toString(){
    Animal::toString();
    cout<<"It's a carnivore, this subclass of animals feeds exclusively on meat."<<endl;
    cout<<"Favourite meat is: "<<favMeat<<endl;    
}

string Carnivore::getType(){
    return Animal::getType();
}

int Carnivore::getAge(){
    return Animal::getAge();
}

string Carnivore::getMeat(){
    return this->favMeat;
}