#include "Names.hpp"

string Names::getRandomName(){
    int r;
    r = rand() % 410;
    return this->names[r];
}

string Names::getRandomMeat(){
    int r;
    r = rand() % 20;
    return this->meats[r];
}

string Names::getRandomPlant(){
    int r;
    r = rand() % 12;
    return this->plants[r];
}

string Names::getRandomFood(){
    int r;
    r = rand() % 2;
    if (r == 0){
        r = rand() % 20;
        return this->meats[r];
    }
    r = rand() % 12;
    return this->plants[r];

}

string Names::getRandomFurPattern(){
    int r;
    r = rand() % 6;
    return this->patterns[r];
}