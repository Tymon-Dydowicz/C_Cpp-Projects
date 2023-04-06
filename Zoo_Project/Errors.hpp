#include <iostream>
using namespace std;

class negativeError{
private:
    int number;
public:
    negativeError(int);
    ~negativeError() {}
    int getNumber();
};

class tooBigError{
private:
    int number;
public:
    tooBigError(int);
    ~tooBigError() {}
    int getNumber();
};

class typeError{
private:
    string name;
public:
    typeError(string);
    ~typeError() {}
    string getName();
};


