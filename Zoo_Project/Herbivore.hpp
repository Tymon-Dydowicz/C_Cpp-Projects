#include "Animal.hpp"

class Herbivore : public Animal{
private:
    string favPlant;

public:
    Herbivore(int, string, string, string);
    ~Herbivore() {}

    virtual void toString() override;
    virtual string getType() override;
    virtual int getAge() override;
    virtual string getPlant();

};