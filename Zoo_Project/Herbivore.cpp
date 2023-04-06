#include "Herbivore.hpp"

Herbivore::Herbivore(int iage, string iname, string type, string iplant) : Animal(iage, iname, type){
    favPlant = iplant;
}

void Herbivore::toString(){
    Animal::toString();
    cout<<"it's a herbivore"<<endl<<"Herbivores are animals that feed exclusively on plants and nothing else."<<endl;
    cout<<"Favourite plant is: "<<favPlant<<endl;
}

string Herbivore::getType(){
    return Animal::getType();
}

int Herbivore::getAge(){
    return Animal::getAge();
}

string Herbivore::getPlant(){
    return this->favPlant;
}