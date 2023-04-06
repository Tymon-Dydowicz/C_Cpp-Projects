#include "Turtle.hpp"

Turtle::Turtle(int iage, string iname, string iplant, int isize) : Herbivore(iage, iname, "Turtle", iplant){
    sizeOfShell = isize;
}

void Turtle::toString(){
    Herbivore::toString();
    cout<<"Turtles are herbivores, they are small animals covered by a hard shell in which they hide in case of danger."<<endl;
    cout<<"The size of the shell of this specimen is: "<<sizeOfShell<<endl;
}

string Turtle::getType(){
    return Herbivore::getType();
}

int Turtle::getAge(){
    return Herbivore::getAge();
}

string Turtle::getPlant(){
    return Herbivore::getPlant();
}

int Turtle::getShellSize(){
    return this->sizeOfShell;
}