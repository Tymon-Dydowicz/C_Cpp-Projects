#include "Animal.hpp"

class Carnivore : public Animal{
private:
    string favMeat;

public:
    Carnivore(int, string, string, string);
    ~Carnivore() {}

    virtual void toString() override;
    virtual string getType() override;
    virtual int getAge() override;
    virtual string getMeat();

};