#include "Errors.hpp"

negativeError::negativeError(int inum){
    this->number = inum;
}

tooBigError::tooBigError(int inum){
    this->number = inum;
}

typeError::typeError(string iname){
    this->name = iname;
}

int tooBigError::getNumber(){
    return this->number;
}

int negativeError::getNumber(){
    return this->number;
}

string typeError::getName(){
    return this->name;
}