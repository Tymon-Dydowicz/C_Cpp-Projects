#include "Peacock.hpp"

Peacock::Peacock(int iage, string iname, string ifood, int isize) : Omnivore(iage, iname, "Peacock", ifood){
    sizeOfFeathers = isize;
}

void Peacock::toString(){
    Omnivore::toString();
    cout<<"Peacocks are omnivores with big beautiful tails that are made of big colorful feathers."<<endl;
    cout<<"The size of feathers of this specimen is: "<<sizeOfFeathers<<endl;
}

string Peacock::getType(){
    return Omnivore::getType();
}

int Peacock::getAge(){
    return Omnivore::getAge();
}

string Peacock::getFood(){
    return Omnivore::getFood();
}

int Peacock::getFeatherSize(){
    return this->sizeOfFeathers;
}