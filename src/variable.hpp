#pragma once
#include <string>

template <class T>
class Variable
{
public:
    Variable(std::string name, T default_value = NULL);
    T get();
    void set(T);

private:
    T value;
    std::string name;
};