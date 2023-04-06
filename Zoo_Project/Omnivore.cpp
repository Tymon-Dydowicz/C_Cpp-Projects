#include "Omnivore.hpp"

Omnivore::Omnivore(int iage, string iname, string type, string ifood) : Animal(iage, iname, type){
    favFood = ifood;
}

void Omnivore::toString(){
    Animal::toString();
    cout<<"It's an omnivore, omnivores are animals that feed on both meat and plants."<<endl;
    cout<<"Favourite food is: "<<favFood<<endl;
}

string Omnivore::getType(){
    return Animal::getType();
}

int Omnivore::getAge(){
    return Animal::getAge();
}

string Omnivore::getFood(){
    return this->favFood;
}