#include "variable.hpp"

using std::string;
using std::any;
using std::any_cast;

Variable::Variable(string name)
: name{name} {}

void Variable::set(any value)
{
    value = value;
}

template <typename T>
T Variable::get()
{
    return any_cast<T>(value);
}