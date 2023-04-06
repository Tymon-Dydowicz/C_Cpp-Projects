#include "Herbivore.hpp"


class Turtle : public Herbivore{
private:
    int sizeOfShell;

public:
    Turtle(int, string, string, int);
    ~Turtle() {}

    void toString() override;
    string getType() override;
    int getAge() override;
    string getPlant() override;
    int getShellSize();
};