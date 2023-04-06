#include <iostream>
#include <vector>
#include <limits.h>
#include "Names.hpp"
#include "Tiger.hpp"
#include "Peacock.hpp"
#include "Turtle.hpp"
using namespace std;



template <typename T>
class zoo{
private: 
    Names Names;
    std::vector<T*> zooResidents;
    int pBreed;
    int pExtinct;
    

public:
    zoo(int ib, int ie){
        pBreed = ib;
        pExtinct = ie;
    }

    int getAmountOfAnimals(){
        return zooResidents.size();
    }

    void operator+=(T* resident){
            zooResidents.push_back(resident);
    }

    void operator-=(T* resident){
        for (int i = 0; i < zooResidents.size(); i++){
            if (zooResidents[i] == resident){
                zooResidents.erase(zooResidents.begin()+i);
                break;
            }
        }
    }

    void toString(){
        cout<<"Animals contained in the zoo are: "<<endl;
        for(int i = 0; i < zooResidents.size(); i ++){
            cout<<"------------------------------ "<<i+1<<" --------------------------------"<<endl;            
            zooResidents[i]->toString();
            cout<<"------------------------------------------------------------------"<<endl;            
        }
        cout<<this->getAmountOfAnimals()<<endl;
    }

    void addRandomAnimal(){
        string animalType, Types[3] = {"Tiger", "Peacock", "Turtle"};
        int r;
        r = rand() % 3;
        animalType = Types[r];
        if (animalType == "Tiger"){
            T* child = new Tiger(1 + rand() % 50, Names.getRandomName(), Names.getRandomMeat(), Names.getRandomFurPattern());
            *this += child;
        }

        if (animalType == "Peacock"){
            T* child = new Peacock(1+ rand() % 50, Names.getRandomName(), Names.getRandomFood(), 5 + rand() % 20);
            *this += child;
        }

        if (animalType == "Turtle"){
            T* child = new Turtle(1 + rand() % 50, Names.getRandomName(), Names.getRandomPlant(), 10 + rand() % 35);
            *this += child;
        }
    }

    void breed(){
        double p1, p2;
        int rp, rt, rc1, rc2, childAge, length;
        T* parents[2];
        T* child;
        string types[2], childType, childName;
        length = zooResidents.size();
        for(int i = 0; i < length; i++){
            parents[0] = zooResidents[i];
            p1 = (double)rand()/RAND_MAX * 100;        
            p2 = (double)rand()/RAND_MAX * 100;
            if (p1 < pBreed){
                rp = rand() % length;
                parents[1] = zooResidents[rp];

                types[0] = parents[0]->getType();
                types[1] = parents[1]->getType();
                rt = rand() % sizeof(types)/sizeof(types[0]);
                childType = types[rt];
                childAge = (parents[0]->getAge() + parents[1]->getAge())/2;
                childName = Names.getRandomName();
                if ((childType == "Tiger") && (types[1 - rt] == "Tiger")){
                    Tiger* parentsT[2];
                    parentsT[0] = (Tiger*) parents[0];
                    parentsT[1] = (Tiger*) parents[1];
                    string childFurPattern, childFavMeat, meats[2], patterns[2];
                    meats[0] = parentsT[0]->getMeat();
                    meats[1] = parentsT[1]->getMeat();
                    patterns[0] = parentsT[0]->getFurPattern();
                    patterns[1] = parentsT[1]->getFurPattern(); 
                    rc1 = rand() % sizeof(meats)/sizeof(meats[0]);
                    rc2 = rand() % sizeof(patterns)/sizeof(patterns[0]);  
                    childFavMeat = meats[rc2];       
                    childFurPattern = patterns[rc2];

                    T* child = new Tiger(childAge, Names.getRandomName(), childFavMeat, childFurPattern);
                    *this += child;
                }
                else if ((childType == "Tiger") && (types[1 - rt] != "Tiger")){
                    Tiger* parent;
                    parent = (Tiger*) parents[rt];
                    string childFurPattern, childFavMeat;
                    childFavMeat = parent->getMeat();
                    childFurPattern = parent->getFurPattern();

                    T* child = new Tiger(childAge, Names.getRandomName(), childFavMeat, childFurPattern);
                    *this += child;
                }

                else if((childType == "Peacock") && (types[1 - rt] == "Peacock")){
                    Peacock* parentsP[2];
                    parentsP[0] = (Peacock*) parents[0];
                    parentsP[1] = (Peacock*) parents[1];

                    string childFavFood, foods[2];
                    int childSizeOfFeathers;
                    foods[0] = parentsP[0]->getFood();
                    foods[1] = parentsP[1]->getFood();
                    rc1 = rand() % sizeof(foods)/sizeof(foods[0]);
                    childFavFood = foods[rc1];
                    childSizeOfFeathers = (parentsP[0]->getFeatherSize() + parentsP[1]->getFeatherSize())/2;

                    T* child = new Peacock(childAge, Names.getRandomName(), childFavFood, childSizeOfFeathers);
                    *this += child;
                }

                else if((childType == "Peacock") && (types[1 - rt] != "Peacock")){
                    Peacock* parent;
                    parent = (Peacock*) parents[rt];
                    string childFavFood;
                    int childSizeOfFeathers;
                    childFavFood = parent->getFood();
                    childSizeOfFeathers = parent->getFeatherSize();
                    
                    T* child = new Peacock(childAge, Names.getRandomName(), childFavFood, childSizeOfFeathers);
                    *this += child;
                }

                else if((childType == "Turtle") && (types[1 - rt] == "Turtle")){
                    Turtle* parentsTu[2];
                    parentsTu[0] = (Turtle*) parents[0];
                    parentsTu[1] = (Turtle*) parents[1];

                    string childFavPlant, plants[2];
                    int childSizeOfShell;
                    plants[0] = parentsTu[0]->getPlant();
                    plants[1] = parentsTu[1]->getPlant();
                    rc1 = rand() % sizeof(plants)/sizeof(plants[0]);
                    childFavPlant = plants[rc1];
                    childSizeOfShell = (parentsTu[0]->getShellSize() + parentsTu[1]->getShellSize())/2;

                    T* child = new Turtle(childAge, Names.getRandomName(), childFavPlant, childSizeOfShell);
                    *this += child;                   
                }

                else if((childType == "Turtle") && (types[1 - rt] != "Turtle")){
                    Turtle* parent;
                    parent = (Turtle*) parents[rt];
                    string childFavPlant;
                    int childSizeOfShell;
                    childFavPlant = parent->getPlant();
                    childSizeOfShell = parent->getShellSize();

                    T* child = new Turtle(childAge, Names.getRandomName(), childFavPlant, childSizeOfShell);
                    *this += child;
                }
            }

            if(p2 < pExtinct){
                *this -= parents[0];
                i--;
                length--;
            }
        }
    }
};