#include "Carnivore.hpp"

class Tiger : public Carnivore{
private:
    string furPattern;

public:
    Tiger(int, string, string, string);
    ~Tiger() {}

    void toString() override;
    string getType() override;
    int getAge() override;
    string getMeat() override;
    string getFurPattern();

};
