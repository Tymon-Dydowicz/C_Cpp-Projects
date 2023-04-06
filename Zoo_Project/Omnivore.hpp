#include "Animal.hpp"

class Omnivore : public Animal{
private:
    string favFood;

public:
    Omnivore(int, string, string, string); 
    ~Omnivore() {}

    virtual void toString() override;
    virtual string getType() override;
    virtual int getAge() override;
    virtual string getFood();
};