#include <iostream>
#include <vector>
#pragma once
using namespace std;

class Animal
{
private:
    int age;
    string name;
    string type;
public:
    Animal(int, string, string);
    ~Animal() {}

    virtual string getType();
    virtual void toString();
    virtual int getAge();
};
