#pragma once
#include <string>
#include <any>

class Variable
{
public:
    Variable(std::string name);
    void set(std::any input);

    template <typename T>
    T get();

private:

    std::any value;
    std::string name;
};