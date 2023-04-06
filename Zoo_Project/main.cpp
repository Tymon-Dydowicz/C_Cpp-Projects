#include "Zoo.hpp"
#include "Errors.hpp"

int main(){
    int pBreed, pExtinct, startingNumberOfAnimals;
    try{
    cout<<"How many animals do you wish to have in your zoo at the beggining? Input a positive integer number: "<<endl;
    cin>>startingNumberOfAnimals;
    if (startingNumberOfAnimals < 0) {throw(negativeError(startingNumberOfAnimals));}
    else if (cin.fail()) {throw(typeError("startingNumberOfAnimals"));}

    cout<<"Enter the probability of succesful breeding in the zoo in percentage points:"<<endl;
    cin>>pBreed;
    if (pBreed < 0) {throw(negativeError(pBreed));}
    else if (pBreed > 100) {throw(tooBigError(pBreed));}
    else if (cin.fail()) {throw(typeError("pBreed"));}

    cout<<"Enter the probability of parent extinction in the zoo in percentage points:"<<endl;
    cin>>pExtinct;
    if (pExtinct < 0) {throw(negativeError(pExtinct));}
    else if (pExtinct > 100) {throw(tooBigError(pExtinct));}
    else if (cin.fail()) {throw(typeError("pExtinct"));}

    }

    catch(negativeError num) {
        cout<<"The number you have input is negative: "<<num.getNumber()<<endl<<"Please input a positive integer number"<<endl;
        exit(2137);
    }
    catch(tooBigError num){
        cout<<"One of the probabilites ("<<num.getNumber()<<") you input was bigger than 100 please keep it in between 0 and 100"<<endl;
        exit(420);
    }
    catch(typeError str){
        cout<<"One of the values your input was of incorect type ("<<str.getName()<<") when it was supposed to be int, please only input ints";
        exit(69);
    }

    zoo<Animal> ourZoo(pBreed, pExtinct);
    Names Names;

    srand(151936); //SEEDING

    while(ourZoo.getAmountOfAnimals()<startingNumberOfAnimals){
        ourZoo.addRandomAnimal();
    }
    while (ourZoo.getAmountOfAnimals() < 100){  
        ourZoo.breed();
        ourZoo.toString();
        if (ourZoo.getAmountOfAnimals() == 0){
            cout<<"The zoo has lost all of it's animals";
            break;
        }
    }
    
    cout<<"FINISHED";
    return 0;
}

