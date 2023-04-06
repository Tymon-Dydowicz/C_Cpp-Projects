#include "Tiger.hpp"

Tiger::Tiger(int iage, string iname, string imeat, string ifur) : Carnivore(iage, iname, "Tiger", imeat){
    furPattern = ifur;
}

void Tiger::toString(){
    Carnivore::toString();
    cout<<"Tiger is a carnivore, mostly recognized by its orange fur with black stripes. This big cat is an apex predator and orignates from Asia with some exceptions to their look."<<endl;
    cout<<"The fur pattern of this specimen is: "<<furPattern<<endl;
}

string Tiger::getType(){
    return Carnivore::getType();
}

int Tiger::getAge(){
    return Carnivore::getAge();
}

string Tiger::getMeat(){
    return Carnivore::getMeat();
}

string Tiger::getFurPattern(){
    return this->furPattern;
}