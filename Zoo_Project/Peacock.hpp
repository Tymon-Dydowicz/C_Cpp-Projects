#include "Omnivore.hpp"

class Peacock : public Omnivore{
private:
    int sizeOfFeathers;

public:
    Peacock(int, string, string, int);
    ~Peacock() {}

    void toString() override;
    string getType() override;
    int getAge() override;
    string getFood() override;
    int getFeatherSize();

};