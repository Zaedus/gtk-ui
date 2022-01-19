#include "variable.hpp"

template <typename T>
Variable<T>::Variable(std::string name, T default_value)
: value{default_value}, name{name}
{}

template <typename T>
void Variable<T>::set(T v)
{
    value = v;
}

template <typename T>
T Variable<T>::get()
{
    return value;
}
